//
// Created by Xingyuan Wang on 3/3/16.
//

// In the code below, I want the message “burned” to be displayed
// exactly one time, and for this message to be displayed only
// after the loop has completed executing. With the code as written,
// I do not get that behavior (in fact, I have a double-delete bug
// and the program crashes). Add one or more new functions to class
// Container so that I get the desired behavior (do not change the
// pass function).

#include <iostream>

using std::cout;

class HotPotato {
public:
    ~HotPotato(void) { cout << "burned\n"; }
};

class Container {
    HotPotato* pot;
public:
    Container(void) { pot = new HotPotato; }
    Container(Container&& that) { move(std::move(that)); }
    Container& operator=(Container&& rhs) {
        if (this != &rhs) {
            delete pot;
            move(std::move(rhs));
        }
        return *this;
    }
    ~Container() { delete pot; }

private:
    void move(Container&& that) {
        pot = that.pot;
        that.pot = nullptr;
    }
};

Container pass(Container& c) { return std::move(c); }

int main(void) {
    Container c;
    for (int k = 0; k < 10; k += 1) {
        c = pass(c);
    }
}
