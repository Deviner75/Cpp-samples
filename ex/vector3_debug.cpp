#include "vector3.h"
#include <iostream>

int main()
{
    Vector3 a(1);
    Vector3 b(1, 2);
    Vector3 c;

    std::cout << "Vector3 v=v: ";
    c = Vector3::Set(1, 2, 3);
    Vector3 d(a);
    std::cout << "Vector3 set(1,2,3): ";
    c = Vector3::Set(1, 2, 3);
    c.Print();
    std::cout << "Vector3 addition v+v: (2,2,0) ";
    c = a + b;
    c.Print();
    std::cout << "Vector3 addition +=v: (1,0,0) ";
    c = Vector3::Set(0, 0, 0);
    c += a;
    c.Print();
    std::cout << "Vector3 substraction v-v: (0,-2,0) ";
    c = Vector3::Set(0, 0, 0);
    c = a - b;
    c.Print();
    std::cout << "Vector3 substraction -=v: (-1,0,0) ";
    c = Vector3::Set(0, 0, 0);
    c -= a;
    c.Print();
    std::cout << "Vector3 multiplication v*const: (2, 4, 6) ";
    c = Vector3::Set(1, 2, 3);
    c = c * 2;
    c.Print();
    std::cout << "Vector3 multiplication *=v: (2, 4, 6) ";
    c = Vector3::Set(1, 2, 3);
    c *= 2;
    c.Print();
    std::cout << "Vector3 division v/const: (2.5, -5, 50) ";
    c = Vector3::Set(5, -10, 100);
    c = c / 2;
    c.Print();
    std::cout << "Vector3 division /=const: (2.5, -5, 50) ";
    c = Vector3::Set(5, -10, 100);
    c /= 2;
    c.Print();

    std::cout << "Vector3 dot: (0.447214) ";
    float dot = Vector3::Dot(a.Normalized(), b.Normalized());
    std::cout << dot << std::endl;

    std::cout << "Vector3 cross: (0, 0, 0.89) ";
    Vector3 cross = Vector3::Cross(a.Normalized(), b.Normalized());
    cross.Print();

    std::cout << "Vector3 lerp: (1, .8, 0) ";
    Vector3 lerp = Vector3::Lerp(a, b, .4);
    lerp.Print();

    return 0;
}
