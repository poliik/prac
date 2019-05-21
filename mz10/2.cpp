#include <iostream>

/*
S -> aAd
A -> aAd | B
B -> bCc
C -> bCc | eps
*/

void C(int k)
{
    if (k > 0) {
        std::cout << 'b';
        C(k - 1);
        std::cout << 'c';
    }
}

void B(int k)
{
    std::cout << 'b';
    C(k - 1);
    std::cout << 'c';
}

void A(int k, int len)
{
    if (k) {
        std::cout << 'a';
        A(k - 1, len - 2);
        std::cout << 'd';
    } else {
        B(len / 2);
    }
}

void S(int k, int len)
{
    if (k) {
        std::cout << 'a';
        A(k - 1, len - 2);
        std::cout << 'd' << std::endl;
        S(k - 1, len);
    }
}
int main()
{
    int len;
    std::cin >> len;
    if (len >= 4 && !(len % 2)) {
        S(len / 2 - 1, len);
    }
    return 0;
}
