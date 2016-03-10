//
// Created by Xingyuan Wang on 3/9/16.
//

// Design and implement a class Number with the following behavior.
// • Any int or double can be promoted to a Number without using a type cast.
// • Two Numbers can be added with operator+(). You do not need to support any
//   other arithmetic with Numbers.
// • When adding two Numbers, if both the values are known to be integers, then
//   integer arithmetic should be used to add them. If one (or both) of the numbers
//   is a double, then double-precision floating point should be used to add the numbers.
// Use an object-oriented approach (i.e., avoid if statements or comparable designs)

#include <iostream>

using std::cout;
using std::endl;
using std::ostream;

class Base {
public:
    virtual ~Base() {};
    virtual Base* plus(Base* that) const = 0;
    virtual Base* plusWithInt(int x) const = 0;
    virtual Base* plusWithDouble(double x) const = 0;
    virtual Base* clone(void) const = 0;
    virtual ostream& print(ostream& out) const = 0;
};

class Double : public Base {
    double val;
public:
    Double(double x) : val{x} {}
    ~Double() override {};
    Base* plus(Base* that) const override { return that->plusWithDouble(val); }
    Base* plusWithInt(int x) const override { return new Double(val + x); }
    Base* plusWithDouble(double x) const override { return new Double(val + x); }
    Base* clone(void) const override { return new Double{val}; };
    ostream& print(ostream& out) const override {
        out << val;
        return out;
    }
};

class Integer : public Base {
    int val;
public:
    Integer(int x) : val{x} {}
    ~Integer() override {};
    Base* plus(Base* that) const override { return that->plusWithInt(val); }
    Base* plusWithInt(int x) const override { return new Integer(val + x); }
    Base* plusWithDouble(double x) const override { return new Double(val + x); }
    Base* clone(void) const override { return new Integer{val}; }
    ostream& print(ostream& out) const override {
        out << val;
        return out;
    }
};

class Number {
    Base* ptr;
public:
    Number(int x) { ptr = new Integer(x); }
    Number(double x) { ptr = new Double(x); }
    Number(Base* p) : ptr(p) {}
    Number& operator=(Number const& rhs) {
        if (this != &rhs) {
            delete ptr;
            ptr = rhs.ptr->clone();
        }
        return *this;
    }
    ~Number() { delete ptr; }
    Number plus(Number const& y) const { return this->ptr->plus(y.ptr); }
    ostream& print(ostream& out) const { return ptr->print(out); }
};

Number operator+(Number const& x, Number const& y) { return x.plus(y); }
ostream& operator<<(ostream& out, Number const& rhs) { return rhs.print(out); }

int main() {
    Number x = 3;
    Number y = 5;
    Number z = 2.5;
    x = x + y; // uses int arithmetic, x is assigned 8
    x = x + z; // uses double arithmetic, x is assigned 10.5
    cout << x + z << endl; // uses double arithmetic, prints 13.0
}
