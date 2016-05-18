//
// Created by Xingyuan Wang on 3/3/16.
//

#include <iostream>

// Recall that a wrapper can make working with inheritance hierarchies
// more convenient. In our examples from class, actual objects were stored
// on the heap (allocated with new) and the wrapper contained a pointer to
// the object. Consider the following abstract base class. To keep things
// simple, I’ve only included one virtual function for the Base class
// (it is pure virtual in the Base class).
// a) Create a copy constructor for the wrapper class. If you need to make
//    any changes to the Base class (or either Derived1 or Derived2), please
//    make those changes.
// b) I want to be able to invoke doit on the wrapper using . syntax (i.e.,
//    I do not want to use * or ->) Provide a doit method for the wrapper
// c) Write a destructor for your Wrapper. Note that the Base class is
//    abstract and has no obvious need for a destructor. I believe it actually
//    does need a destructor. Write one that is appropriate for the class.
// d) Write an assignment operator so that I can assign a Derived1 or Derived2
//   object (not a pointer) to a Wrapper.
// The main program shown below requires all four parts (a-d) to be implemented
// correctly so that it prints, “the answer is 42” with no errors or memory leaks.

using std::string;
using std::cout;

class Base {
public:
    virtual void doit(void) const = 0;
    virtual Base* clone(void) const = 0;
    virtual ~Base() {};
};

class Derived1 : public Base {
    string x;
public:
    Derived1(string x) { this->x = x; }
    Derived1(Derived1 const& that) { x = that.x; }
    virtual void doit(void) const override { cout << x; }
    virtual Derived1* clone(void) const override { return new Derived1{*this}; }
    virtual ~Derived1() {}
};
class Derived2 : public Base {
    int x;
public:
    Derived2(int x) { this->x = x; }
    Derived2(Derived2 const& that) { x = that.x; }
    virtual void doit(void) const override { cout << x << "\n"; }
    virtual Derived2* clone(void) const override { return new Derived2{*this};}
    virtual ~Derived2() {}
};

class Wrap {
    Base* ptr; // ptr will be nullptr or will point to the heap
public:
    Wrap(void) { ptr = nullptr; }
    Wrap(Wrap const& that) {
        ptr = that.ptr->clone();
    }
    ~Wrap() { delete ptr; }
    Wrap& operator=(const Base& rhs) {
        delete ptr;
        ptr = rhs.clone();
        return *this;
    }
    void doit(void) const { ptr->doit(); }
};

void fun(Wrap x) { // x is pass-by-value (i.e copy)
    x.doit();
}

int main(void) {
    Wrap w;
    w = Derived1("the answer is ");
    fun(w);
    w = Derived2(42);
    fun(w);
}
