#include <iostream>

class MyVector {
private:
    int sz;
    int currentIndex = 0;
    double* elem;

private:
    void resize(double* arr);

public:
    MyVector(int s);

    MyVector(const MyVector& arg);
    MyVector(MyVector&& arg);

    ~MyVector();

    void push_back(double val);
    int size();
    double GetValue(int index);
    void SetValue(int index, double val);
    double& operator[](int index);

    MyVector& operator=(const MyVector& a);
    MyVector& operator=(MyVector&& a);
};

MyVector Fill(std::istream& stream);