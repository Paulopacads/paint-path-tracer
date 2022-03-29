#include "material.hpp"

struct MaterialInfo Material::getMaterialInfo(Vector3 point)
{
    return {
        .color = Vector3(), .nrefr = 0, .kd = 0, .ks = 0, .kt = 0, .ka = 0
    };
}

UniformMaterial::UniformMaterial(Vector3 color, double nrefr, double kd,
                                 double ks, double kt, double ka)
{
    this->color = color;
    this->nrefr = nrefr;
    this->kd = kd;
    this->ks = ks;
    this->kt = kt;
    this->ka = ka;
}

UniformMaterial::UniformMaterial(nlohmann::json json)
    : UniformMaterial(Vector3(json["col"]), json["nref"], json["kd"],
                      json["ks"], json["kt"], json["ka"])
{}

struct MaterialInfo UniformMaterial::getMaterialInfo(Vector3 point)
{
    return { .color = this->color,
             .nrefr = this->nrefr,
             .kd = this->kd,
             .ks = this->ks,
             .kt = this->kt,
             .ka = this->ka };
}

ApplyMaterial::ApplyMaterial(double (*apply)(double), double nrefr, double kd,
                             double ks, double kt, double ka)
{
    this->apply = apply;
    this->nrefr = nrefr;
    this->kd = kd;
    this->ks = ks;
    this->kt = kt;
    this->ka = ka;
}

ApplyMaterial::ApplyMaterial(nlohmann::json json, double (*apply)(double))
    : ApplyMaterial(apply, json["nref"], json["kd"], json["ks"], json["kt"],
                    json["ka"])
{}

struct MaterialInfo ApplyMaterial::getMaterialInfo(Vector3 point)
{
    return { .color = Vector3(this->apply(point.x), this->apply(point.y),
                              this->apply(point.z)),
             .nrefr = this->nrefr,
             .kd = this->kd,
             .ks = this->ks,
             .kt = this->kt,
             .ka = this->ka };
}
