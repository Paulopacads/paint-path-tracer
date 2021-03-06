#include "vector3.hpp"

Vector3::Vector3()
    : Vector3(0, 0, 0)
{}

Vector3::Vector3(double x, double y, double z)
    : x(x)
    , y(y)
    , z(z)
{}

Vector3::Vector3(nlohmann::json json)
    : Vector3(json["x"], json["y"], json["z"])
{}

Vector3 Vector3::mult(const Vector3 &v) const
{
    return Vector3(this->x * v.x, this->y * v.y, this->z * v.z);
}

double Vector3::dot(const Vector3 &v) const
{
    return this->x * v.x + this->y * v.y + this->z * v.z;
}

Vector3 Vector3::cross(const Vector3 &v) const
{
    return Vector3(this->y * v.z - this->z * v.y, this->z * v.x - this->x * v.z,
                   this->x * v.y - this->y * v.x);
}

Vector3 Vector3::norm() const
{
    return *this * (1 / this->size());
}

double Vector3::size() const
{
    return sqrt(this->x * this->x + this->y * this->y + this->z * this->z);
}

Vector3 Vector3::operator*(const double &l) const
{
    return Vector3(l * this->x, l * this->y, l * this->z);
}

Vector3 Vector3::operator/(const double &l) const
{
    return Vector3(this->x / l, this->y / l, this->z / l);
}

Vector3 Vector3::operator+(const Vector3 &v) const
{
    return Vector3(this->x + v.x, this->y + v.y, this->z + v.z);
}

Vector3 Vector3::operator-(const Vector3 &v) const
{
    return Vector3(this->x - v.x, this->y - v.y, this->z - v.z);
}

std::ostream &operator<<(std::ostream &out, const Vector3 &vec)
{
    return out << "x: " << vec.x << "; y: " << vec.y << "; z: " << vec.z << ";";
}
