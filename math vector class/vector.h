#pragma once
// Vector class
// Might be used to represent a position in 3D space, or a 3D direction with a length

// includes
#include "math.h"
#include <iostream>

class Vector {
public:
    float x, y, z;

    // Constructors
    // Initializes to the values of another vector
    Vector(const Vector& v);
    // Initializes to the input values
    Vector(float X = 0, float Y = 0, float Z = 0);

    // Operators
    // Creates a new value based on its arguments, such as creating a vector from its components
    Vector Set(float x, float y, float z);
    // Assigns to the values of another vector
    Vector& operator=(Vector const& obj);
    // Returns the values of this vector plus another vector
    Vector operator+(Vector const& obj) const;
    // Adds to this vector, the values of another vector
    Vector& operator+=(Vector const& obj);
    // Returns the values of this vector minus another vector
    Vector operator-(Vector const& obj) const;
    // Subtracts from this vector the values of another vector
    Vector& operator-=(Vector const& obj);
    // Returns a negated copy of this vector
    Vector operator-() const;

    // Returns the values of this vector times a scalar
    Vector operator*(float s) const;
    // Multiplies the values of this vector by a scalar
    Vector& operator*=(float s);
    // Returns the values of this vector divided by a scalar
    Vector operator/(float s) const;
    // Divides the values of this vector by a scalar
    Vector& operator/=(float s);

    // Returns the squared magnitude of this vector
    float Length() const;
    // Returns a unit-vector in the same direction
    Vector Normalized() const;
    // Linear Interpolation between two vectors. Usage: x.lerp(obj1)
    Vector Lerp(Vector const& obj1, float t) const;
    // Returns the dot product of two vectors
    float Dot(Vector const& obj1) const;
    // Returns the cross product of two vectors
    Vector Cross(Vector const& obj1) const;
    // Prints values to the console
    void Print();
};

// Returns a new value based on its arguments, such as creating a vector from its components
Vector Set(float X, float Y, float Z);
// Linear Interpolation between two vectors. Usage: x = lerp(obj1, obj2)
Vector Lerp(Vector const& obj1, Vector const& obj2, float t);
// Returns the dot product of two vectors
float Dot(Vector const& obj1, Vector const& obj2);
// Returns the cross product of two vectors
Vector Cross(Vector const& obj1, Vector const& obj2);