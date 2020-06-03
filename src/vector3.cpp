// includes
#include "vector3.h"
#include "math.h"
#include <iostream>

Vector3::Vector3(Vector3 const& v)
    : x(v.x)
    , y(v.y)
    , z(v.z)
{
}

Vector3::Vector3(float X /*0*/, float Y /*0*/, float Z /*0*/)
    : x(X)
    , y(Y)
    , z(Z)
{
}

Vector3& Vector3::operator=(Vector3 const& obj)
{
    x = obj.x;
    y = obj.y;
    z = obj.z;

    return *this;
}

bool Vector3::operator==(Vector3 const& obj1) const
{
    return x == obj1.x && y == obj1.y && z == obj1.z;
}

Vector3 Vector3::operator+(Vector3 const& obj) const
{
    Vector3 result;
    result.x = x + obj.x;
    result.y = y + obj.y;
    result.z = z + obj.z;

    return result;
}

Vector3& Vector3::operator+=(Vector3 const& obj)
{
    x += obj.x;
    y += obj.y;
    z += obj.z;

    return *this;
}

Vector3 Vector3::operator-(Vector3 const& obj) const
{
    Vector3 result;
    result.x = x - obj.x;
    result.y = y - obj.y;
    result.z = z - obj.z;

    return result;
}

Vector3& Vector3::operator-=(Vector3 const& obj)
{
    x -= obj.x;
    y -= obj.y;
    z -= obj.z;

    return *this;
}

Vector3 Vector3::operator-() const
{
    return Vector3(-x, -y, -z);
}

Vector3 Vector3::operator*(float s) const
{
    Vector3 result;
    result.x = x * s;
    result.y = y * s;
    result.z = z * s;

    return result;
}

Vector3& Vector3::operator*=(float s)
{
    x *= s;
    y *= s;
    z *= s;

    return *this;
}

Vector3 Vector3::operator/(float s) const
{
    Vector3 scaled;
    scaled.x = x / s;
    scaled.y = y / s;
    scaled.z = z / s;

    return scaled;
}

Vector3& Vector3::operator/=(float s)
{
    x /= s;
    y /= s;
    z /= s;

    return *this;
}

float Vector3::operator[](int index) const
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

Vector3 Vector3::operator*(Matrix3 const& obj1)
{
    Vector3 result;
    result.x = obj1.p_mtx[0][0] * x + obj1.p_mtx[1][0] * y + obj1.p_mtx[2][0] * z;
    result.y = obj1.p_mtx[0][1] * x + obj1.p_mtx[1][1] * y + obj1.p_mtx[2][1] * z;
    result.z = obj1.p_mtx[0][2] * x + obj1.p_mtx[1][2] * y + obj1.p_mtx[2][2] * z;

    return result;
}

float Vector3::Length() const
{
    return sqrt(x * x + y * y + z * z);
}

Vector3 Vector3::Normalized() const
{
    return (*this) / Length();
}

// Static functions
// SET LERP DOT CROSS

Vector3 Vector3::Set(float X, float Y, float Z)
{
    return Vector3(X, Y, Z);
}

Vector3 Vector3::Lerp(Vector3 const& obj1, Vector3 const& obj2, float t)
{
    return obj1 + (obj2 - obj1) * t;
}

float Vector3::Dot(Vector3 const& obj1, Vector3 const& obj2)
{
    return obj1.x * obj2.x + obj1.y * obj2.y + obj1.z * obj2.z;
}

Vector3 Vector3::Cross(Vector3 const& obj1, Vector3 const& obj2)
{
    Vector3 result;
    result.x = obj1.y * obj2.z - obj1.z * obj2.y;
    result.y = obj1.z * obj2.x - obj1.x * obj2.z;
    result.z = obj1.x * obj2.y - obj1.y * obj2.x;

    return result;
}

void Vector3::Print()
{
    std::cout << x << ", " << y << ", " << z << std::endl;
}
