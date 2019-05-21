#include <iostream>
#include <sstream>
char c;
std::string::iterator it;

void gc()
{
    ++it;
    c = *it;
}
void ABS();
void AB();
void A();
void ABC();
void ABCS();
void ACS();
void S1()
{
    return;
}
void AS()
{
    if (c == '1') {
        gc();
        AB();
    } else if (c == '0') {
        gc();
        A();
    } else if (c == '_') {
        gc();
        S1();
    } else {
        throw c;
    }
}
void AC()
{
    if (c == '1') {
        gc();
        ABS();
    } else if (c == '0') {
        gc();
        AS();
    } else {
        throw c;
    }
}
void AB()
{
    if (c == '1') {
        gc();
        ABC();
    } else if (c == '0') {
        gc();
        AC();
    } else {
        throw c;
    }
}
void A()
{
    if (c == '1') {
        gc();
        AB();
    } else if (c == '0') {
        gc();
        A();
    } else {
        throw c;
    }
}

void ABC()
{
    if (c == '1') {
        gc();
        ABCS();
    } else if (c == '0') {
        gc();
        ACS();
    } else {
        throw c;
    }
}
void ABCS()
{
    if (c == '1') {
        gc();
        ABCS();
    } else if (c == '0') {
        gc();
        ACS();
    } else if (c == '_') {
        gc();
        S1();
    } else {
        throw c;
    }
}
void ACS()
{
    if (c == '1') {
        gc();
        ABS();
    } else if (c == '0') {
        gc();
        AS();
    } else if (c == '_') {
        gc();
        S1();
    } else {
        throw c;
    }
}
void ABS()
{
    if (c == '1') {
        gc();
        ABC();
    } else if (c == '0') {
        gc();
        AC();
    } else if (c == '_') {
        gc();
        S1();
    } else {
        throw c;
    }
}

void S()
{
    if (c == '1') {
        gc();
        AB();
    } else if (c == '0') {
        gc();
        A();
    } else {
        throw c;
    }
}


int main()
{
    std::string s;
    while (std::cin >> s) {
        s.push_back('_');
        it = s.begin() - 1;
        try {
            gc();
            S();
            std::cout << 1 << std::endl;
        } catch (...) {
            std::cout << 0 << std::endl;
        }
    }
    return 0;
}
