#include "light_source.hpp"

LightSource::LightSource(Vector3 position, Vector3 color, double lightness)
    : position(position)
    , color(color)
    , lightness(lightness)
{}

PointLightSource::PointLightSource(Vector3 position, Vector3 color,
                                   double lightness)
    : LightSource(position, color, lightness)
{}

SphereLightSource::SphereLightSource(Vector3 position, Vector3 color,
                                     double lightness, double radius)
    : LightSource(position, color, lightness)
    , radius(radius)
{}
