/*
S-> 1A0
A-> 1A0 | 0B1
B-> 0B1 | eps
*/
#include <iostream>
char c;
void gc()
{
    std::cin >> c;
}
void A();
void B();
void S()
{
    if (c == '1') {
        gc();
        A();
        std::cout << 0;
        if (c != '0') {
            throw 1;
        }
    } else {
        throw 1;
    }
}

void A()
{
    if (c == '1') {
        gc();
        A();
        if (c != '0') {
            throw 1;
        }
        gc();
        std::cout << 0;
    } else if (c == '0') {
        std::cout << 1;
        gc();
        B();
        if (c != '1') {
            throw 1;
        }
        gc();
        std::cout << 0;
    } else {
        throw 1;
    }
}

void B()
{
    if (c == '0') {
        std::cout << 1;
        gc();
        B();
        if (c != '1') {
            throw 1;
        }
        gc();
        std::cout << 0;
    }
}

int main()
{
    while (std::cin >> c) {
        try {
            S();
            std::cout << std::endl;
        } catch (int) {}
    }
    return 0;
}
