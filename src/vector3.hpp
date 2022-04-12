#pragma once

#include <ostream>

#include "../libs/json.cpp"

class Vector3
{
public:
    double x;
    double y;
    double z;

    Vector3();
    Vector3(nlohmann::json);
    Vector3(double, double, double);
    double dot(const Vector3 &) const;
    Vector3 cross(const Vector3 &v) const;
    Vector3 norm() const;
    double size() const;
    Vector3 operator*(const double &) const;
    Vector3 operator/(const double &) const;
    Vector3 operator+(const Vector3 &) const;
    Vector3 operator-(const Vector3 &) const;
    friend std::ostream &operator<<(std::ostream &, const Vector3 &);
};

std::ostream &operator<<(std::ostream &, const Vector3 &);
