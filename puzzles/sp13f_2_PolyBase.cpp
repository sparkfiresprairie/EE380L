//
// Created by Xingyuan Wang on 3/3/16.
//

// For this example, I’m using the same Base, Derived1 and Derived2
// examples from question 1 which do not have multiple inheritance.
// In the code below, I have two constructors and two assignment operators.
// The doit() function works correctly when a PolyBase is created using
// either constructor (when constructed with a string argument, the doit
// method prints a string, when constructed with an integer argument, the
// doit method prints an integer. However, if I attempt to change the type
// of the PolyBase using an assignment operator (e.g., construct the object
// with Derived1 but assign the object a Derived2), then the doit method
// produces garbage output.
// a) Why do the assignment operators not work? Specifically, what aspect of
//    the object needs to be changed that isn’t changed by the assignment
//    operator? (write your answer with 10 words or fewer).
// b) In the space below, rewrite one of the assignment operators so that
//    the object properly changes type. After assigning a PolyBase a Derived2
//    object, doit should print an int (even if the object was constructed
//    originally with a string).
// Hint: If you forget the syntax for placement new, it’s
//                   new (p) T(args);
// to construct an object of type T at the address pointed to by p.

#include <iostream>
#include <string>

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

class PolyBase {
    union {
        Derived1 d1;
        Derived2 d2;
    };
public:
    PolyBase(const string& s) : d1(s) {}
    PolyBase(int x) : d2(x) {}
    void doit(void) const {
        ((Base*) &d1)->doit();
    }
    PolyBase& operator=(const Derived1& d1) {
        this->d1 = d1;
        return *this;
    }
    PolyBase& operator=(const Derived2& d2) {
        this->~PolyBase();
        new (this) Derived2{ d2 };
        return *this;
    }
    ~PolyBase() {}
};

int main (void) {
    PolyBase pb{"the answer is "};
    pb = Derived2{42};
    pb.doit();
}