#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>

unsigned steps = 0;
typedef std::map<std::string, std::multimap<char, std::string>> MyMap;
void f(MyMap &mp, std::string &cur, unsigned i, std::string &input,
    std::vector<std::string> &ends, std::multimap<std::string, std::string> &eps)
{
    if (i == input.size()) {
        if (find(ends.begin(), ends.end(), cur) != ends.end()) {
            throw i;
        }
    } else {
        for (auto it = mp[cur].begin(); it != mp[cur].end(); ++it) {
            if (it->first == input[i]) {
                if (i + 1 > steps) {
                    steps = i + 1;
                }
                f(mp, it->second, i + 1, input, ends, eps);
            }
        }
        for (auto it = eps.begin(); it != eps.end(); ++it) {
            if (it->first == cur) {
                if (i > steps) {
                    steps = i;
                }
                f(mp, it->second, i, input, ends, eps);
            }
        }
    }

}

int main()
{
    MyMap mp;
    std::string cur, next, symb;
    std::cin >> cur;
    std::multimap<std::string, std::string> eps;
    while (cur != "END") {
        std::cin >> symb >> next;
        if (symb == "eps") {
            eps.insert(std::pair<std::string, std::string>(cur, next));
        } else {
            mp[cur].insert(std::pair<char, std::string>(symb[0], next));
        }
        std::cin >> cur;
    }
    std::vector<std::string> ends;
    std::cin >> cur;
    while (cur != "END") {
        ends.push_back(cur);
        std::cin >> cur;
    }
    std::cin >> cur >> next;

    try {
        f(mp, cur, 0, next, ends, eps);
        std::cout << 0 << std::endl << steps << std::endl;
    } catch (unsigned cnt) {
        std::cout << 1 << std::endl << cnt << std::endl;
    }
    return 0;
}
