#include "vector.cpp"

int main()
{
    Vector a(1);
    Vector b(2, 3);
    Vector c;

    std::cout << "Vector set(x,y,z): ";
    c = Set(1, 2, 3);
    c.Print();
    std::cout << "Vector v.set(x,y,z): ";
    c.Set(3, 2, 1);
    c.Print();
    std::cout << "Vector addition v+v: ";
    c = Set(0, 0, 0);
    c = a + b;
    c.Print();
    std::cout << "Vector addition +=v: ";
    c = Set(0, 0, 0);
    c += a;
    c.Print();
    std::cout << "Vector substraction v-v: ";
    c = Set(0, 0, 0);
    c = a - b;
    c.Print();
    std::cout << "Vector substraction -=v: ";
    c = Set(0, 0, 0);
    c -= a;
    c.Print();
    std::cout << "Vector multiplication v*const: ";
    c = Set(1, 2, 3);
    c = c * 2;
    c.Print();
    std::cout << "Vector multiplication *=v: ";
    c = Set(1, 2, 3);
    c *= 2;
    c.Print();
    std::cout << "Vector division v/const: ";
    c = Set(5, -10, 100);
    c = c / 2;
    c.Print();
    std::cout << "Vector division /=v: ";
    c = Set(5, -10, 100);
    c /= 2;
    c.Print();
    std::cout << "Vector dot: ";
    float dot = Dot(a.Normalized(), b.Normalized());
    std::cout << dot << std::endl;
    std::cout << "Vector cross: ";
    Vector cross = Cross(a.Normalized(), b.Normalized());
    cross.Print();
    std::cout << "Vector lerp: ";
    Vector lerp = Lerp(a, b, .4);
    lerp.Print();

    return 0;
}
