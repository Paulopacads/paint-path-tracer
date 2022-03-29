#pragma once

#include "vector3.hpp"

struct MaterialInfo
{
    Vector3 color;
    double nrefr;
    double kd;
    double ks;
    double kt;
    double ka;
    double ke;
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
    double kd;
    double ks;
    double kt;
    double ka;
    double ke;

    UniformMaterial(Vector3, double, double, double, double, double, double);
    UniformMaterial(nlohmann::json);
    struct MaterialInfo getMaterialInfo(Vector3);
};

class ApplyMaterial : public Material
{
public:
    double (*apply)(double);
    double nrefr;
    double kd;
    double ks;
    double kt;
    double ka;
    double ke;

    ApplyMaterial(double (*)(double), double, double, double, double, double, double);
    ApplyMaterial(nlohmann::json, double (*)(double));
    struct MaterialInfo getMaterialInfo(Vector3);
};
