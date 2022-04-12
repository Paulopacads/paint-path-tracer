#pragma once

#include "vector3.hpp"

struct MaterialInfo // describes material info for one position
{
    Vector3 color;
    double nrefr; // refraction coeff. of the object
    double ke; // emission
    double kd; // diffusion
    double ks; // specularity
    double kt; // transparency
};

class Material
{
public:
    virtual struct MaterialInfo getMaterialInfo(Vector3);
};

class UniformMaterial : public Material
{
public:
    Vector3 color;
    double nrefr;
    double ke;
    double kd;
    double ks;
    double kt;

    UniformMaterial(Vector3, double, double, double, double, double);
    UniformMaterial(nlohmann::json);
    struct MaterialInfo getMaterialInfo(Vector3);
};
