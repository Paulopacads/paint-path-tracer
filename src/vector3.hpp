#pragma once

#include <ostream>

#include "../libs/json.hpp"

class Vector3 // or Color
{
public:
    double x; // or red channel
    double y; // or green channel
    double z; // or blue channel

    Vector3(); // (0, 0, 0) init
    Vector3(nlohmann::json);
    Vector3(double, double, double);

    Vector3 operator*(const double &) const;
    Vector3 operator/(const double &) const;
    Vector3 operator+(const Vector3 &) const;
    Vector3 operator-(const Vector3 &) const;

    Vector3 mult(const Vector3 &) const; // mult of each var from vectors
    double dot(const Vector3 &) const; // dot product
    Vector3 cross(const Vector3 &v) const; // cross product
    Vector3 norm() const; // for vect with size = 1
    double size() const;

    friend std::ostream &operator<<(std::ostream &, const Vector3 &);
};

std::ostream &operator<<(std::ostream &, const Vector3 &);
