#include "scene.hpp"

Scene::Scene(Camera camera, Vector3 sky)
    : camera(camera)
    , sky(sky)
{
    objects = {};
}

struct NextObject
{
    Object *object;
    double distance;
};

inline struct NextObject getNextObject(Scene *scene, Vector3 origin,
                                       Vector3 vector)
{
    struct NextObject res = { NULL, HUGE_VAL };
    for (Object *object : scene->objects)
    {
        double distance = object->intersect(origin, vector);
        if (distance > 0 && distance < res.distance)
        {
            res.distance = distance;
            res.object = object;
        }
    }

    return res;
}

inline Vector3 hemisphere(double u1, double u2)
{
    double r = sqrt(1. - u1 * u1);
    double phi = 2 * M_PI * u2;
    return Vector3(cos(phi) * r, sin(phi) * r, u1);
}

Vector3 Scene::castRay(Vector3 origin, Vector3 vector, int depth, Halton *gen1,
                       Halton *gen2)
{
    if (depth >= 20)
        return Vector3();

    struct NextObject next = getNextObject(this, origin, vector);
    if (next.object == NULL)
        return this->sky;

    Vector3 impact = origin + vector * next.distance;
    Vector3 normal = next.object->normal(impact);
    struct MaterialInfo material = next.object->getMaterialInfo(impact);

    Vector3 color = Vector3(1, 1, 1) * material.ke * 2;

    //gen1->next();
    double r = gen1->get();

    // computation of a diffuse impact
    if (r <= material.kd)
    {
        gen1->next();
        gen2->next();

        Vector3 new_dir = normal + hemisphere(gen1->get(), gen2->get());
        Vector3 bnc =
            castRay(impact, new_dir, depth + 1, gen1, gen2);

        return color + material.color.mult(bnc) * new_dir.dot(normal) * .1;
    }

    // computation of a specular impact
    if (r <= material.kd + material.ks)
    {
        Vector3 new_dir = vector - normal * vector.dot(normal) * 2;

        return color
            + castRay(impact, new_dir.norm(), depth + 1, gen1, gen2);
    }

    // computation of a transparent impact
    double nrefr = 1 / material.nrefr;
    if (normal.dot(vector) > 0)
    {
        normal = normal * -1;
        nrefr = 1 / nrefr;
    }

    double c1 = normal.dot(vector) * -1;
    double c2 = 1 - nrefr * nrefr * (1 - c1 * c1);
    if (c2 <= 0)
        return Vector3();

    Vector3 new_dir = vector * nrefr + normal * (nrefr * c1 - sqrt(c2));
    return color
        + castRay(impact, new_dir.norm(), depth + 1, gen1, gen2);
}
