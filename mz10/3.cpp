#include <iostream>
#include <map>
#include <vector>
#include <algorithm>
int main()
{
    std::map<char, std::vector<std::string>> mp;
    char c;
    std::string s;
    while (std::cin >> c >> s) {
        mp[c].push_back(s);
    }
    std::vector<char> v{'S'};

    unsigned size = 0;
    while (1) {
        if (v.size() == size) {
            break;
        } else {
            size = v.size();
        }
        for (unsigned i = 0; i < size; ++i) {
            for (auto &right : mp[v[i]]) {
                for (auto it = right.begin(); it != right.end(); ++it) {
                    if (std::find(v.begin(), v.end(), *it) == v.end()) {
                        v.push_back(*it);
                    }
                }
            }
        }
    }

    for (auto it = mp.begin(); it != mp.end(); ++it) {
        if (std::find(v.begin(), v.end(), it->first) != v.end()) {
            for (auto &str : it->second) {
                int flag = 0;
                for (auto &x : str) {
                    if (std::find(v.begin(), v.end(), x) == v.end()) {
                        flag = 1;
                        break;
                    }
                }
                if (!flag) {
                    std::cout << it->first << ' ' << str << std::endl;
                }
            }
        }
    }
    return 0;
}
