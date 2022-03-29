#include <cmath>
#include <iostream>
#include <math.h>

#include "scene.hpp"

Scene::Scene(Camera camera, Vector3 ambiant, Vector3 sky)
    : camera(camera)
    , ambiant(ambiant)
    , sky(sky)
{
    objects = {};
    sources = {};
}

inline struct NextObject getNextObject(Scene *scene, Vector3 origin,
                                       Vector3 vector)
{
    struct NextObject res = { NULL, HUGE_VAL };
    for (Object *object : scene->objects)
    {
        struct NextObject temp = object->intersect(origin, vector);
        if (temp.distance > 0 && temp.distance < res.distance)
        {
            res.distance = temp.distance;
            res.object = temp.object;
        }
    }

    return res;
}

inline Vector3 computeLightning(Scene *scene, Vector3 contact, Vector3 vector,
                                Vector3 normal, struct NextObject next)
{
    struct MaterialInfo material = next.object->getMaterialInfo(contact);

    Vector3 diffuseComponent = scene->ambiant * material.ka;
    Vector3 specularComponent = Vector3();

    for (LightSource *source : scene->sources)
    {
        Vector3 lightRay = source->position - contact;
        Vector3 lightRayNorm = lightRay.norm();
        struct NextObject toLight =
            getNextObject(scene, contact + lightRayNorm * .0001, lightRayNorm);

        if (toLight.object == NULL || toLight.distance > lightRay.size())
        {
            Vector3 lightReflection =
                (lightRayNorm - normal * (lightRayNorm * 2).dot(normal)).norm();

            diffuseComponent = diffuseComponent
                + source->color * source->lightness * lightRayNorm.dot(normal)
                    / lightRay.size();

            specularComponent = specularComponent
                + source->color * pow(lightReflection.dot(vector), 15)
                    * source->lightness;
        }
        else if (toLight.object->getMaterialInfo(contact).kt != 0)
        {
            struct MaterialInfo toLightMat =
                toLight.object->getMaterialInfo(contact);
            Vector3 lightReflection =
                (lightRayNorm - normal * (lightRayNorm * 2).dot(normal)).norm();

            diffuseComponent = diffuseComponent
                + source->color * source->lightness * lightRayNorm.dot(normal)
                    * toLightMat.kt / toLightMat.nrefr / lightRay.size();

            specularComponent = specularComponent
                + source->color * pow(lightReflection.dot(vector), 15)
                    * source->lightness * toLightMat.kt / toLightMat.nrefr;
        }
    }

    Vector3 color = material.color * material.kd;
    diffuseComponent.x *= color.x;
    diffuseComponent.y *= color.y;
    diffuseComponent.z *= color.z;

    specularComponent = specularComponent * material.ks;
    return diffuseComponent + specularComponent;
}

inline Vector3 computeRefraction(Scene *scene, Vector3 contact, Vector3 vector,
                                 Vector3 normal, struct NextObject next)
{
    double n = next.object->getMaterialInfo(contact).nrefr;
    double cosI = normal.dot(vector);
    if (cosI < 0)
        cosI = -cosI;
    else
    {
        n = 1 / n;
        normal = normal * -1;
    }

    double sinT2 = n * n * (1 - cosI * cosI);
    if (1 - sinT2 < 0)
        return (vector - normal * (vector * 2).dot(normal)).norm();

    double cosT = sqrt(1 - sinT2);
    Vector3 vect = vector * n + normal * (n * cosI - cosT);
    //  std::cout << "entry angle: " << acos(vector.norm().dot(normal.norm())) /
    //  M_PI * 180
    //            << "\nexit angle: " << acos(vect.norm().dot(normal.norm() *
    //            -1)) / M_PI * 180
    //            << "\n\n";
    return vect;
}

Vector3 Scene::castRay(Vector3 origin, Vector3 vector, int depth)
{
    struct NextObject next = getNextObject(this, origin, vector);

    if (next.object != NULL)
    {
        Vector3 contact = origin + vector * next.distance;
        struct MaterialInfo material = next.object->getMaterialInfo(contact);
        Vector3 normal = next.object->normal(contact).norm();

        Vector3 result = computeLightning(this, contact, vector, normal, next);

        if (depth)
        {
            if (material.ks > 0)
            {
                Vector3 refl =
                    (vector - normal * (vector * 2).dot(normal)).norm();
                result = result
                    + castRay(contact + refl * .0001, refl, depth - 1)
                        * material.ks;
            }
            if (material.kt > 0)
            {
                Vector3 refr =
                    computeRefraction(this, contact, vector, normal, next)
                        .norm();
                result = result
                    + castRay(contact + refr * .0001, refr, depth - 1)
                        * material.kt;
            }
        }

        return result;
    }

    return this->sky;
}