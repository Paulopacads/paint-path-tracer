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

Triangle::Triangle(Material *material, Vector3 coord_a, Vector3 coord_b,
                   Vector3 coord_c)
    : Object(material)
{
    this->coord_a = coord_a;
    this->coord_b = coord_b;
    this->coord_c = coord_c;
}

struct NextObject Triangle::intersect(Vector3 origin, Vector3 vector)
{
    double eps = 1e-4;
    Vector3 ba = this->coord_a - this->coord_b;
    Vector3 bc = this->coord_c - this->coord_b;
    Vector3 h = vector.cross(bc);

    double a = ba.dot(h);
    if (a > -eps && a < eps)
        return { NULL, HUGE_VAL };

    double f = 1 / a;
    Vector3 bo = origin - this->coord_b;

    double u = f * bo.dot(h);
    if (u < 0 || u > 1)
        return { NULL, HUGE_VAL };

    Vector3 q = bo.cross(ba);

    double v = f * vector.dot(q);
    if (v < 0 || u + v > 1)
        return { NULL, HUGE_VAL };

    float t = f * bc.dot(q);
    if (t > eps)
        return { this, t };
    else
        return { NULL, HUGE_VAL };
}

Vector3 Triangle::normal(Vector3 point)
{
    Vector3 ba = this->coord_a - this->coord_b;
    Vector3 bc = this->coord_c - this->coord_b;
    return ba.cross(bc).norm();
}
