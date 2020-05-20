#include "vector.h"
#include <iostream>

int main()
{
    Vector a(1);
    Vector b(1, 2);
    Vector c;

    std::cout << "Vector set(1,2,3): ";
    c = Vector::Set(1, 2, 3);
    c.Print();
    std::cout << "Vector addition v+v: (2,2,0) ";
    c = a + b;
    c.Print();
    std::cout << "Vector addition +=v: (1,0,0) ";
    c = Vector::Set(0, 0, 0);
    c += a;
    c.Print();
    std::cout << "Vector substraction v-v: (0,-2,0) ";
    c = Vector::Set(0, 0, 0);
    c = a - b;
    c.Print();
    std::cout << "Vector substraction -=v: (-1,0,0) ";
    c = Vector::Set(0, 0, 0);
    c -= a;
    c.Print();
    std::cout << "Vector multiplication v*const: (2, 4, 6) ";
    c = Vector::Set(1, 2, 3);
    c = c * 2;
    c.Print();
    std::cout << "Vector multiplication *=v: (2, 4, 6) ";
    c = Vector::Set(1, 2, 3);
    c *= 2;
    c.Print();
    std::cout << "Vector division v/const: (2.5, -5, 50) ";
    c = Vector::Set(5, -10, 100);
    c = c / 2;
    c.Print();
    std::cout << "Vector division /=const: (2.5, -5, 50) ";
    c = Vector::Set(5, -10, 100);
    c /= 2;
    c.Print();

    std::cout << "Vector dot: (0.447214) ";
    float dot = Vector::Dot(a.Normalized(), b.Normalized());
    std::cout << dot << std::endl;

    std::cout << "Vector cross: (0, 0, 0.89) ";
    Vector cross = Vector::Cross(a.Normalized(), b.Normalized());
    cross.Print();

    std::cout << "Vector lerp: (1, .8, 0) ";
    Vector lerp = Vector::Lerp(a, b, .4);
    lerp.Print();

    return 0;
}
