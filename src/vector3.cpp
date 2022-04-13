#include "vector3.hpp"

Vector3::Vector3()
{
    this->x = 0;
    this->y = 0;
    this->z = 0;
}

Vector3::Vector3(double x, double y, double z)
{
    this->x = x;
    this->y = y;
    this->z = z;
}

Vector3::Vector3(nlohmann::json json)
{
    this->x = json["x"];
    this->y = json["y"];
    this->z = json["z"];
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
