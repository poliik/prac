#include <iostream>
#include <algorithm>
#include <vector>
#include <cstring>

std::string s;
bool comp(int i, int j)
{
    return std::strcmp(&s[i], &s[j]) < 0;
}
int main()
{
    std::getline(std::cin, s);
    unsigned i = s.size() - 1;
    for (; i >= 0 && isspace(s[i]); --i) {}
    s.resize(i + 1);
    std::vector<int> a(s.size());
    for (i = 0; i < s.size(); ++i) {
        a[i] = i;
    }
    std::stable_sort(a.begin(), a.end(), comp);
    for (const auto &x : a){
        std::cout << x << std::endl;
    }
    return 0;
}
