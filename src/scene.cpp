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

// get the next object on the ray; {null, infty} if no object
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

// uniform distribution on hemisphere with random parameters
// > https://cseweb.ucsd.edu/classes/sp17/cse168-a/CSE168_07_Random.pdf
// > from Steve Rotenberg ~ slide 31
inline Vector3 hemisphere(double u1, double u2)
{
    double r = sqrt(1. - u1 * u1);
    double phi = 2 * M_PI * u2;
    return Vector3(cos(phi) * r, sin(phi) * r, u1);
}

Vector3 Scene::castRay(Vector3 origin, Vector3 vector, int depth, Halton *gen1,
                       Halton *gen2, Halton *rnd)
{
    if (depth >= 20) // we could implement Russian Roulette
        return Vector3(); // from a certain depth to avoid brutal stop

    struct NextObject next = getNextObject(this, origin, vector);
    if (next.object == NULL) // no hit
        return this->sky;

    Vector3 impact = origin + vector * next.distance;
    Vector3 normal = next.object->normal(impact);
    struct MaterialInfo material = next.object->getMaterialInfo(impact);

    Vector3 color = Vector3(1, 1, 1) * material.ke * 2;

    // kd + ks + kt = 1, we evaluate a random to get the way we're bouncing
    // 3 possibilities :
    //  - r < kd : diffusion bounce;
    //  - kd < r < ks : specular bounce;
    //  - ks < r : transparency "bounce"
    double r = rnd->next();

    // computation of a diffuse impact
    if (r <= material.kd)
    {
        Vector3 new_dir = normal + hemisphere(gen1->next(), gen2->next());
        Vector3 bnc = castRay(impact, new_dir, depth + 1, gen1, gen2, rnd);

        return color + material.color.mult(bnc) * new_dir.dot(normal) * .1;
    }

    // computation of a specular impact
    if (r <= material.kd + material.ks)
    {
        Vector3 new_dir = vector - normal * vector.dot(normal) * 2;

        return color + castRay(impact, new_dir, depth + 1, gen1, gen2, rnd);
    }

    // compute material1 to material2 refraction index
    double nrefr = 1 / material.nrefr; // from air to material
    if (normal.dot(vector) > 0) // coming from inside the object ? (vector and
                                // normal in same direction)
    {
        normal = normal * -1; // correct normal direction
        nrefr = 1 / nrefr; // from material to air
    }

    double c1 = normal.dot(vector) * -1;
    double c2 = 1 - nrefr * nrefr * (1 - c1 * c1);
    if (c2 < 0) // angle of refraction beyond critical angle -> no refraction
        return Vector3();

    Vector3 new_dir = vector * nrefr + normal * (nrefr * c1 - sqrt(c2));
    return color + castRay(impact, new_dir, depth + 1, gen1, gen2, rnd);
}
