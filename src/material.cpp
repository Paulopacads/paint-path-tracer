#include "material.hpp"

struct MaterialInfo Material::getMaterialInfo(Vector3 point)
{
    return {
        .color = Vector3(), .nrefr = 0, .ke = 0, .kd = 0, .ks = 0, .kt = 0
    };
}

UniformMaterial::UniformMaterial(Vector3 color, double nrefr, double ke,
                                 double kd, double ks, double kt)
{
    this->color = color;
    this->nrefr = nrefr;
    this->ke = ke;
    this->kd = kd;
    this->ks = ks;
    this->kt = kt;
}

UniformMaterial::UniformMaterial(nlohmann::json json)
    : UniformMaterial(Vector3(json["col"]), json["nref"], json["ke"],
                      json["kd"], json["ks"], json["kt"])
{}

struct MaterialInfo UniformMaterial::getMaterialInfo(Vector3 point)
{
    return { .color = this->color,
             .nrefr = this->nrefr,
             .ke = this->ke,
             .kd = this->kd,
             .ks = this->ks,
             .kt = this->kt };
}
