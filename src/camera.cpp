#include "camera.hpp"

Camera::Camera(Vector3 center, Vector3 looking, Vector3 up, double FOV,
               double distance, double ratio)
{
    this->center = center;
    this->direction = (looking - center).norm();
    this->up = up.norm();
    this->right = this->direction.cross(this->up).norm();

    this->betaFOV = FOV;
    this->alphaFOV = FOV * ratio;
    this->distance = distance;
}
