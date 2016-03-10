#include <iostream>

using std::cout;
using std::endl;

class Base {
public:
    virtual ~Base() { cout << "~Base()" << endl; }
};

class Derived : public Base {
    int x;
public:
    virtual ~Derived() { cout << "~Derived()" << endl; }
};

int main (void) {
    Base* p = new Derived[10];
    delete[] (Derived*)p;
}