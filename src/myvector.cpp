#include "myvector.h"
#include <iostream>

void MyVector::resize(double* arr)
{
    double* newArr = new double[sz * 2];

    for (int i = 0; i < sz; i++) {
        newArr[i] = elem[i];
    }

    for (int j = sz; j < sz * 2; j++) {
        newArr[j] = 0;
    }

    delete[] elem;
    elem = nullptr;
    elem = newArr;
    sz *= 2;
}

MyVector::MyVector(int s)
    : sz(s)
    , elem(new double[s])
{
    for (int i = 0; i < s; ++i)
        elem[i] = 0;
}

MyVector::MyVector(const MyVector& arg)
    : sz(arg.sz)
    , elem(new double[arg.sz])
{
    std::copy(arg.elem, arg.elem + sz, elem);
}

MyVector::MyVector(MyVector&& arg)
    : sz(arg.sz)
    , elem(arg.elem)
{
    arg.elem = nullptr;
    arg.sz = 0;
    arg.currentIndex = 0;
}

MyVector::~MyVector()
{
    std::cout << "Calling the desctructor" << std::endl;
    delete[] elem;
}

void MyVector::push_back(double val)
{
    if (currentIndex < sz) {
        elem[currentIndex] = val;
        currentIndex++;
    } else {
        resize(elem);
        elem[currentIndex] = val;
    }
}

int MyVector::size()
{
    return sz;
}

double MyVector::GetValue(int index)
{
    return elem[index];
}

void MyVector::SetValue(int index, double val)
{
    elem[index] = val;
}

double& MyVector::operator[](int index)
{
    return elem[index];
}

MyVector& MyVector::operator=(const MyVector& a)
{
    double* p = new double[a.sz];
    std::copy(a.elem, a.elem + a.sz, p);
    delete[] elem;
    elem = p;
    sz = a.sz;
    return *this;
}

MyVector& MyVector::operator=(MyVector&& a)
{
    delete[] elem;
    elem = a.elem;
    sz = a.sz;
    a.elem = nullptr;
    a.sz = 0;
    return *this;
}

MyVector Fill(std::istream& stream)
{
    std::cout << "Enter Number" << std::endl;
    MyVector res(2);
    int counter = 0;
    for (double x; stream >> x;) {
        res.push_back(x);
        counter++;
        if (counter > 20) {
            return res;
        }
    }
    return res;
}