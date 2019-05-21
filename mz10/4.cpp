#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>

int main()
{
    std::map<std::string, std::map<char, std::string>> mp;
    std::string cur, next;
    std::cin >> cur;
    char c;
    while (cur != "END") {
        std::cin >> next;
        c = next[0];
        std::cin >> next;
        mp[cur][c] = next;
        std::cin >> cur;
    }
    std::vector<std::string> ends;
    std::cin >> cur;
    while (cur != "END") {
        ends.push_back(cur);
        std::cin >> cur;
    }
    std::cin >> cur >> next;
    int steps = 0;
    bool good = 1;
    for (auto i = next.begin(); i != next.end(); ++i) {
        c = *i;
        auto it = mp[cur].find(c);
        if (it != mp[cur].end()) {
            cur = it->second;
            ++steps;
        } else {
            good = 0;
            break;
        }
    }
    if (find(ends.begin(), ends.end(), cur) == ends.end()) {
        good = 0;
    }
    std::cout << good << std::endl << steps << std::endl << cur << std::endl;
    return 0;
}
