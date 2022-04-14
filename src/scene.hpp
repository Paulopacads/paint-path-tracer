#pragma once

#include "camera.hpp"
#include "halton.hpp"
#include "object.hpp"

class Scene
{
public:
    std::vector<Object *> objects;
    Camera camera;
    Vector3 sky;

    Scene(Camera, Vector3);
    Vector3 castRay(Vector3, Vector3, int, Halton *, Halton *, Halton *);
};
