#include "vector.h"

Vector::Vector(float X /*0*/, float Y /*0*/, float Z /*0*/)
    : x(X)
    , y(Y)
    , z(Z)
{
}

Vector Vector::Set(float X, float Y, float Z)
{
    x = X;
    y = Y;
    z = Z;
}

Vector& Vector::operator=(Vector const& obj)
{
    x = obj.x;
    y = obj.y;
    z = obj.z;

    return *this;
}

Vector Vector::operator+(Vector const& obj) const
{
    Vector result;
    result.x = x + obj.x;
    result.y = y + obj.y;
    result.z = z + obj.z;

    return result;
}

Vector& Vector::operator+=(Vector const& obj)
{
    x += obj.x;
    y += obj.y;
    z += obj.z;

    return *this;
}

Vector Vector::operator-(Vector const& obj) const
{
    Vector result;
    result.x = x - obj.x;
    result.y = y - obj.y;
    result.z = z - obj.z;

    return result;
}

Vector& Vector::operator-=(Vector const& obj)
{
    x -= obj.x;
    y -= obj.y;
    z -= obj.z;

    return *this;
}

Vector Vector::operator-() const
{
    return Vector(-x, -y, -z);
}

Vector Vector::operator*(float s) const
{
    Vector result;
    result.x = x * s;
    result.y = y * s;
    result.z = z * s;

    return result;
}

Vector& Vector::operator*=(float s)
{
    x *= s;
    y *= s;
    z *= s;

    return *this;
}

Vector Vector::operator/(float s) const
{
    Vector scaled;
    scaled.x = x / s;
    scaled.y = y / s;
    scaled.z = z / s;

    return scaled;
}

Vector& Vector::operator/=(float s)
{
    x /= s;
    y /= s;
    z /= s;

    return *this;
}

float Vector::Length() const
{
    return sqrt(x * x + y * y + z * z);
}

Vector Vector::Normalized() const
{
    return (*this) / Length();
}

Vector Vector::Lerp(Vector const& obj1, float t) const
{
    return (*this) + (obj1 - (*this)) * t;
}

float Vector::Dot(Vector const& obj1) const
{
    return x * obj1.x + y * obj1.y + z * obj1.z;
}

Vector Vector::Cross(Vector const& obj1) const
{
    Vector result;
    result.x = y * obj1.z - z * obj1.y;
    result.y = z * obj1.x - x * obj1.z;
    result.z = x * obj1.y - y * obj1.x;

    return result;
}

Vector Set(float X, float Y, float Z)
{
    return Vector(X, Y, Z);
}

Vector Lerp(Vector const& obj1, Vector const& obj2, float t)
{
    return obj1.Lerp(obj2, t);
}

float Dot(Vector const& obj1, Vector const& obj2)
{
    return obj1.Dot(obj2);
}

Vector Cross(Vector const& obj1, Vector const& obj2)
{
    return obj1.Cross(obj2);
}

void Vector::Print()
{
    std::cout << x << ", " << y << ", " << z << std::endl;
}
