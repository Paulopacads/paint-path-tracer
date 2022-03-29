#include <math.h>

#include "camera.hpp"

Camera::Camera(Vector3 center, Vector3 looking, Vector3 up, double FOV,
               double distance, double ratio)
{
    this->center = center;
    this->direction = (looking - center).norm();
    this->up = up.norm();
    this->right =
        Vector3(this->direction.y * this->up.z - this->direction.z * this->up.y,
                this->direction.z * this->up.x - this->direction.x * this->up.z,
                this->direction.x * this->up.y - this->direction.y * this->up.x)
            .norm();
    this->betaFOV = FOV;
    this->alphaFOV = FOV * ratio;
    this->distance = distance;
}
