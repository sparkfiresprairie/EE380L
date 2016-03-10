//
// Created by Xingyuan Wang on 3/3/16.
//

// The purpose of this question is to ensure that you understood
// object-oriented programming methods. Your solution to this
// problem, cannot contain any “if” statements, and must not use
// “?” operator or use any arrays.
// As you are undoubtedly aware, human children come in two basic
// designs, “Boy” and “Girl”. I’d like to have a general type
// Child which could be either Boy or Girl. All children will play.
// In this problem I want to consider children that play either by
// themselves, or children that play with another child. To
// represent playing, a Child object should have a member function
// (i.e., a method) called “play”. There should be two overloads
// for this function; play(void) and play(Child*). The play methods
// must provide the following behavior.
// When a Boy plays by himself, he plays with action figures (print “Action”)
// When a Girl plays by herself, she plays with dolls (print “Dolls”)
// When a Boy plays with another Boy, they play rough (print “Roughhouse”)
// When a Girl plays with another Girl, they play nice (print “Tea party”)
// When a Boy and Girl play together, they play tag (print “Cooties”)
// a) Define the types Child, Boy and Girl.
// b) Create a factory method that has a 50% chance of creating and returning
//    a Boy and a 50% chance of creating and returning a Girl.
// c) Write a main program that creates two Child objects Alex and Ryan.
//    In your program Alex and Ryan should be initialized by calling your
//    factory method. They could be either boys or girls. Write your program
//    so that it contains three method invocations: Alex plays alone (Alex
//    invokes play(void)), Ryan plays alone (Ryan invokes play(void)) and Alex
//    and Ryan play together (Alex invokes play(Child) where the Child argument
//    is Ryan).
// d) Use a wrapper only if it makes your solution shorter or simpler than the
//    code without a wrapper. Do not have any memory leaks.


#include <iostream>
#include <string>
#include <map>
#include <functional>
#include <cstdlib>

using std::cout;
using std::endl;
using std::string;
using std::map;

class Child {
public:
    virtual void play(void) const = 0;
    virtual void play(Child* other) const = 0;
    virtual void playWithBoy(void) const = 0;
    virtual void playWithGirl(void) const = 0;
};

map<int, std::function<Child*()>> childMap;

class Boy : public Child {
public:
    virtual void play(void) const override { cout << "Action" << endl; }
    virtual void play(Child* other) const override {
        other->playWithBoy();
    }
    virtual void playWithBoy(void) const override { cout << "Roughhouse" << endl; }
    virtual void playWithGirl(void) const override { cout << "Cooties" << endl; }
    static Boy* makeBoy(void) { return new Boy; }
};

struct _InitBoy {
    _InitBoy() { childMap[1] = &Boy::makeBoy; }
};

_InitBoy dummyBoy;


class Girl : public Child {
public:
    virtual void play(void) const override { cout << "Dolls" << endl; }
    virtual void play(Child* other) const override {
        other->playWithGirl();
    }
    virtual void playWithBoy(void) const override { cout << "Cooties" << endl; }
    virtual void playWithGirl(void) const override { cout << "Tea party" << endl; }
    static Girl* makeGirl(void) { return new Girl; };
};


struct _InitGirl {
    _InitGirl() { childMap[0] = &Girl::makeGirl; }
};

_InitBoy dummyGirl;

Child* factory() {
    int coin = rand() % 2;
    return childMap[coin]();
}

int main(void) {
    Child* Alex = factory();
    Child* Ryan = factory();
    Alex->play();
    Ryan->play();
    Alex->play(Ryan);
    delete Alex;
    delete Ryan;
}
