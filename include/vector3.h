#pragma once
// Vector class
// Mathematical structure used to hold 3D points and vectors
// Might be used to represent a position in 3D space, or a 3D direction with a length

#include "matrix3.h"

class Vector3 {
public:
    float x, y, z;

    // Constructors
    // Initializes to the values of another vector
    Vector3(const Vector3& v);
    // Initializes to the input values
    Vector3(float X = 0, float Y = 0, float Z = 0);

    // Operators
    // Assigns to the values of another vector
    Vector3& operator=(Vector3 const& obj);
    // Compares two vectors
    bool operator==(Vector3 const& obj1) const;
    // Returns the values of this vector plus another vector
    Vector3 operator+(Vector3 const& obj) const;
    // Adds to this vector, the values of another vector
    Vector3& operator+=(Vector3 const& obj);
    // Returns the values of this vector minus another vector
    Vector3 operator-(Vector3 const& obj) const;
    // Subtracts from this vector the values of another vector
    Vector3& operator-=(Vector3 const& obj);
    // Returns a negated copy of this vector
    Vector3 operator-() const;

    // Returns the values of this vector times a scalar
    Vector3 operator*(float s) const;
    // Multiplies the values of this vector by a scalar
    Vector3& operator*=(float s);
    // Returns the values of this vector divided by a scalar
    Vector3 operator/(float s) const;
    // Divides the values of this vector by a scalar
    Vector3& operator/=(float s);
    // Returns a component of the vector
    float operator[](int index) const;

    // Transforms a vector by a matrix
    Vector3 operator*(Matrix3 const& obj2);

    // Returns the squared magnitude of this vector
    float Length() const;
    // Returns a unit-vector in the same direction
    Vector3 Normalized() const;

    // Prints values to the console
    void Print();

    // Returns a new value based on its arguments, such as creating a vector from its components
    static Vector3 Set(float X, float Y, float Z);
    // Linear Interpolation between two vectors. Usage: x = lerp(obj1, obj2)
    static Vector3 Lerp(Vector3 const& obj1, Vector3 const& obj2, float t);
    // Returns the dot product of two vectors
    static float Dot(Vector3 const& obj1, Vector3 const& obj2);
    // Returns the cross product of two vectors
    static Vector3 Cross(Vector3 const& obj1, Vector3 const& obj2);
};