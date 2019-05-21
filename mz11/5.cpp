#include <iostream>
#include <string>

int pos(std::string &s, int k)
{
    for (int brac = 0; k >= 0; --k) {
        if (s[k] == ')') {
            ++brac;
        } else if (s[k] == '(') {
            --brac;
        }
        if (!brac) {
            break;
        }
    }
    return k;
}

int main()
{
    std::string s;
    char c;
    while ((c = getchar()) != EOF) {
        if (!isspace(c)) {
            if (c == '+' || c == '-' || c == '*' || c ==  '/') {
                int p = pos(s, s.size() - 1);
                s.insert(p, 1, c);
                p = pos(s, p - 1);
                s.insert(p, 1, '(');
                s.push_back(')');
            } else {
                s.push_back(c);
            }
        }
    }
    std::cout << s;
    return 0;
}
