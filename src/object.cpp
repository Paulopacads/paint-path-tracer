#include <cmath>

#include "object.hpp"

Object::Object(Material *material)
    : material(material)
{}

Object::~Object()
{}

struct NextObject Object::intersect(Vector3 origin, Vector3 vector)
{
    return { NULL, HUGE_VAL };
}

bool Object::contains(Vector3 point)
{
    return false;
}

Vector3 Object::normal(Vector3 point)
{
    return Vector3(HUGE_VAL, HUGE_VAL, HUGE_VAL);
}

struct MaterialInfo Object::getMaterialInfo(Vector3 point)
{
    return this->material->getMaterialInfo(point);
}

Sphere::Sphere(Material *material, Vector3 center, double radius)
    : Object(material)
{
    this->center = center;
    this->radius = radius;
}

struct NextObject Sphere::intersect(Vector3 origin, Vector3 vector)
{
    Vector3 op = this->center - origin;
    double eps = 1e-4;
    double b = op.dot(vector);
    double det = b * b - op.dot(op) + this->radius * this->radius;
    if (det < 0)
        return { this, 0 };
    else
        det = sqrt(det);
    return { this,
             b - det > eps ? b - det : (b + det > eps ? b + det : HUGE_VAL) };
}

bool Sphere::contains(Vector3 point)
{
    return (point - this->center).size() <= this->radius;
}

Vector3 Sphere::normal(Vector3 point)
{
    return point - this->center;
}

Plane::Plane(Material *material, Vector3 norm, double d)
    : Object(material)
{
    this->norm = norm;
    this->d = d;
}

struct NextObject Plane::intersect(Vector3 origin, Vector3 vector)
{
    double eps = 1e-4;
    double d0;
    if ((d0 = norm.dot(vector)) != 0)
    {
        double t = -1 * (norm.dot(origin) + d) / d0;
        if (t > eps)
            return { this, t };
        else
            return { NULL, HUGE_VAL };
    }
    return { NULL, HUGE_VAL };
}

Vector3 Plane::normal(Vector3 point)
{
    return this->norm;
}
