#include <iostream>
#include <string>

/*
тип языка : 0
S = aXPQ
P = YXP | ε
Q = UVQ | ε
aY = aa
aU = a0
0U = 00
0X = 0b
bX = bb
bV = b1
1V = 11
XY = YX
XU = UX
VU = UV
*/

int main()
{
    std::string s;
    while (std::cin >> s) {
        unsigned int n = 0, k = 0;
        int res = 1;
        unsigned int i = 0;
        while (i < s.size() && s[i] == 'a') {
            ++i;
        }
        if (i) {
            n = i;
            while (i < s.size() && s[i] == '0') {
                ++i;
            }
            if (i == n) {
                res = 0;
            } else {
                k = i - n;
                while (i < s.size() && s[i] == 'b') {
                    ++i;
                }
                if ((i - k - n) != n) {
                    res = 0;
                } else {
                    n = i;
                    while (i < s.size() && s[i] == '1') {
                        ++i;
                    }
                    if ((i - n) != k) {
                        res = 0;
                    }
                    if (i != s.size()) {
                        res = 0;
                    }
                }
            }
        } else {
            res = 0;
        }
        std::cout << res << std::endl;
    }
    return 0;
}
