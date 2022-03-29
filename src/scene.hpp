#pragma once

#include <vector>

#include "camera.hpp"
#include "light_source.hpp"
#include "object.hpp"

class Scene
{
public:
    std::vector<Object *> objects;
    Camera camera;
    Vector3 ambiant;
    Vector3 sky;

    Scene(Camera, Vector3, Vector3);
    Vector3 castRay(Vector3, Vector3, int);
};
