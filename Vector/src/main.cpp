// memory leak includes
#define _CRTDBG_MAP_ALLOC

#include "myvector.h"

#include <stdlib.h>
#include <crtdbg.h>

template <class T>
void Print(const T& arg)
{
    std::cout << "The vector elements are : \n";

    for (std::size_t i = 0; i < arg.size(); i++)
    {
        std::cout << arg[i] << ' ';
    }
    std::cout << "\n";
}

int main()
{
    {
        MyVector<float> v;

        std::cout << "v.push_back()" << std::endl;
        int in = 1;
        while (in > 0)
        {
            std::cin >> in;
            v.push_back((float)in);
        }

        std::cout << "v.size(): " << v.size() << std::endl;
        Print(v);

        std::cout << "\nv[1]: " << v[1] << std::endl;

        v.clear();
        std::cout << "\nv.clear()" << std::endl;
        std::cout << "v.size(): " << v.size() << std::endl;

        std::cout << "\nv.push_back() 10 elements" << std::endl;
        in = 10;
        while (in > 0)
        {
            in--;
            v.push_back((float)in);
        }
        std::cout << "v.size(): " << v.size() << std::endl;

        v.resize(30);
        std::cout << "v.resize() 30" << std::endl;
        Print(v);
        std::cout << "v.size(): " << v.size() << std::endl;

        v.resize(2);
        std::cout << "v.resize() 2" << std::endl;
        Print(v);
        std::cout << "v.size(): " << v.size() << std::endl;

        v.reserve(40);
        std::cout << "v.reserve(40) new capacity: " << v.capacity() << std::endl;
        
        MyVector<float> b(v);
        std::cout << "b.size(): " << b.size() << std::endl;
        std::cout << "b.capacity(): " << b.capacity() << std::endl;
        Print(b);

        v.push_back(54);
        v.push_back(74);
        v.push_back(54);
        v.push_back(34);

        b = v;
        std::cout << "b.size(): " << b.size() << std::endl;
        std::cout << "b.capacity(): " << b.capacity() << std::endl;
    }

    // memory leak detection
    _CrtDumpMemoryLeaks();



    return 0;
}