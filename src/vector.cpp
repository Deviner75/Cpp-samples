// includes
#include "vector.h"
#include "math.h"
#include <iostream>

Vector::Vector(float X /*0*/, float Y /*0*/, float Z /*0*/)
    : x(X)
    , y(Y)
    , z(Z)
{
}

Vector& Vector::operator=(Vector const& obj)
{
    x = obj.x;
    y = obj.y;
    z = obj.z;

    return *this;
}

bool Vector::operator==(Vector const& obj1) const
{
    return x == obj1.x && y == obj1.y && z == obj1.z;
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

float Vector::operator[](int index) const
{
    switch (index) {
    case 0:
        return x;
        break;
    case 1:
        return y;
        break;
    case 2:
        return z;
        break;
    default:
        return 1;
    }
}

Vector Vector::operator*(Matrix3 const& obj1)
{
    Vector result;
    result.x = obj1.p_mtx[0][0] * x + obj1.p_mtx[1][0] * y + obj1.p_mtx[2][0] * z;
    result.y = obj1.p_mtx[0][1] * x + obj1.p_mtx[1][1] * y + obj1.p_mtx[2][1] * z;
    result.z = obj1.p_mtx[0][2] * x + obj1.p_mtx[1][2] * y + obj1.p_mtx[2][2] * z;

    return result;
}

float Vector::Length() const
{
    return sqrt(x * x + y * y + z * z);
}

Vector Vector::Normalized() const
{
    return (*this) / Length();
}

// Static functions
// SET LERP DOT CROSS

Vector Vector::Set(float X, float Y, float Z)
{
    return Vector(X, Y, Z);
}

Vector Vector::Lerp(Vector const& obj1, Vector const& obj2, float t)
{
    return obj1 + (obj2 - obj1) * t;
}

float Vector::Dot(Vector const& obj1, Vector const& obj2)
{
    return obj1.x * obj2.x + obj1.y * obj2.y + obj1.z * obj2.z;
}

Vector Vector::Cross(Vector const& obj1, Vector const& obj2)
{
    Vector result;
    result.x = obj1.y * obj2.z - obj1.z * obj2.y;
    result.y = obj1.z * obj2.x - obj1.x * obj2.z;
    result.z = obj1.x * obj2.y - obj1.y * obj2.x;

    return result;
}

void Vector::Print()
{
    std::cout << x << ", " << y << ", " << z << std::endl;
}
