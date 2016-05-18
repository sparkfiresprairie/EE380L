//
// Created by Xingyuan Wang on 3/9/16.
//


// For this problem, I’d like you to design a “personality” object.
// We’ll keep things simple. There are three types of personalities,
// Grumpy, Happy and Indifferent. Personalities can greet other
// personalities and can say goodbye.
// a) For part a, I want you to focus on the classes, the constructors
// and destructors, the makePersonality factory and the farewell method.
// We’ll write the greet method in part b. For this problem, you are
// permitted to use an “if” (or a switch) statement in the makePersonality
// factory only (no other conditional branches are permitted – that includes
// the ? operator in C).
// Implement an object-oriented personality with the three types described
// above. Write makePersonality so that it randomly creates an personality
// of the appropriate type. Write constructors, destructors and any other
// functions you need so that the main program above will run and compile.
// For part (a), the greet method does not need to work. A Grumpy personality
// says farewell by outputting “Leave me alone” to the console. A Happy
// personality says farewell by outputting “Have a nice day!” to the console.
// An Indifferent personality says farewell by outputting “yeah, whatever”
// to the console.
// b) For part b, I want you to write the greet method so that we obtain
// the following behavior. A Grumpy personality greets any Personality
// outputting “Go Away” to the console. Indifferent personalities greet
// other Personalities by outputting “yeah, whatever” to the console and
// Happy Personalities greet other Personalities by outputting “Hi there!”
// In addition, Personalities affect each others’ moods. When a Happy
// Personality greets an Indifferent Personality, the Indifferent personality
// becomes Happy. When a Grumpy Personality greets another Grumpy Personality,
// the Grumpy Personality becomes Indifferent. When a Grumpy Personality greets
// an Indifferent Personality, the Indifferent Personality becomes Grumpy,
// and when a Grumpy Personality greets a Happy Personality, the Happy
// Personality becomes Indifferent (as you can see, happiness is fleeting).
// Any other combination of moods results in no change after the greeting.
// To make it specific, the method a.greet(b) will influence object b, possibly
// causing b to change type (depending on the type of a and b).
// i.  Indifferent personalities never change the mood of the personality they greet
// ii. Happy personalities make Indifferent personalities Happy, but have no
//     effect on Grumpy or Happy personalities.
// iii.Grumpy personalities always have an effect. Grumpy Personalities
//     make both Happy and Grumpy personalities become Indifferent, and make
//     Indifferent personalities become Grumpy.

#include <iostream>

using std::cout;
using std::endl;

class Base {
public:
    virtual void farewell(void) const = 0;
    virtual ~Base() {}
    virtual void greet(Base* that) const = 0;
    virtual void greetByGrumpy(void) = 0;
    virtual void greetByHappy(void) = 0;
    virtual void greetByIndifferent(void) = 0;
};

class Grumpy : public Base {
public:
    void farewell(void) const override { cout << "Leave me alone" << endl; }
    virtual ~Grumpy() {}
    void greet(Base* that) const override {
        cout << "Go Away" << endl;
        that->greetByGrumpy();
    }
    void greetByGrumpy(void) override;
    void greetByHappy(void) override {}
    void greetByIndifferent(void) override {}
};

class Happy : public Base {
public:
    void farewell(void) const override { cout << "Have a nice day!" << endl; }
    virtual ~Happy() {}
    void greet(Base* that) const override {
        cout << "Hi there!" << endl;
        that->greetByHappy();
    }
    void greetByGrumpy(void) override;
    void greetByHappy(void) override {}
    void greetByIndifferent(void) override {}
};

class Indifferent : public Base {
public:
    void farewell(void) const override { cout << "yeah, whatever" << endl; }
    virtual ~Indifferent() {}
    void greet(Base* that ) const override {
        cout << "yeah, whatever" << endl;
        that->greetByIndifferent();
    }
    void greetByGrumpy(void) override;
    void greetByHappy(void) override;
    void greetByIndifferent(void) override {}
};

void Grumpy::greetByGrumpy(void) {
    this->~Grumpy();
    new (this) Indifferent{};
}

void Happy::greetByGrumpy(void) {
    this->~Happy();
    new (this) Indifferent{};
}

void Indifferent::greetByGrumpy(void) {
    this->~Indifferent();
    new (this) Grumpy{};
}

void Indifferent::greetByHappy(void) {
    this->~Indifferent();
    new (this) Happy{};
}

class Personality {
    Base* ptr;
public:
    Personality(Base* p) : ptr(p) {}
    ~Personality() { delete ptr; }
    void farewell(void) { ptr->farewell(); }
    void greet(Personality& that) {
        ptr->greet(that.ptr);
    }
};

Base* makePersonality(void) {
    int coin = rand() % 3;
    if (coin == 0) return new Grumpy{};
    else if (coin == 1) return new Happy{};
    else return new Indifferent{};
}

int main(void) {
    Personality p = makePersonality();
    Personality q = makePersonality();
    Personality r = makePersonality();
    r.greet(p);
    p.greet(q);
    q.greet(p);
    p.farewell();
    q.farewell();
}
