#include <iostream>
#include <sstream>
#include <string>
#include <map>
#include <set>
#include <vector>

void nullable(std::map<char, std::vector<std::string>> &mp, std::map<char, int> &nulls)
{
    bool change = true;
    while (change) {
        change = false;
        for (auto &it: mp) {
            for (auto &rule : it.second) {
                bool good = true;
                for (unsigned i = 0; i < rule.size(); ++i) {
                    if (!isupper(rule[i]) || nulls[rule[i]] != 1) {
                        good = false;
                        break;
                    }
                }
                if (good && nulls[it.first] == -1) {
                    nulls[it.first] = 1;
                    change = true;
                }
            }
        }
    }
}
typedef std::map<char, std::set<char>> MyMap;
void firsts(std::map<char, std::vector<std::string>> &mp,
    MyMap &mfirst, std::map<char, int> &nulls)
{
    bool change = true;
    while (change) {
        change = false;
        for (auto &it: mp) {
            char key = it.first;
            for (auto &rule : it.second) {
                unsigned prev_size = mfirst[key].size();
                for (unsigned i = 0; i < rule.size(); ++i) {
                    char key1 = rule[i];
                    if (!isupper(key1)) {
                        mfirst[key].insert(key1);
                        if (prev_size != mfirst[key].size()) {
                            change = true;
                        }
                        break;
                    }
                    if (key1 != key) {
                        mfirst[key].insert(mfirst[key1].begin(), mfirst[key1].end());
                        if (prev_size != mfirst[key].size()) {
                            change = true;
                        }
                    }
                    if (!nulls[key1]) {
                        break;
                    }
                }
            }
        }
    }
}

void follows(std::map<char, std::vector<std::string>> &mp, MyMap &mfirst,
    std::map<char, int> &nulls, MyMap &follow)
{
    for (auto &it : mp) {
        for (auto &it_rule : it.second) {
            for (auto c = it_rule.begin(); c != it_rule.end() - 1; ++c) {
                if (isupper(*c)) {
                    unsigned next = 1;
                    while (c + next != it_rule.end()) {
                        if (isupper(*(c + next))) {
                            follow[*c].insert(mfirst[*(c + next)].begin(), mfirst[*(c + next)].end());
                            if (!nulls[*(c + next)]) {
                                break;
                            }
                            ++next;
                        } else {
                            follow[*c].insert(*(c + next));
                            break;
                        }
                    }
                }
            }
        }
    }

    bool change = true;
    while (change) {
        change = false;
        for (auto &key_rules : mp) {
            for (auto &rule : key_rules.second) {
                for (unsigned i = rule.size() - 1; i >= 0; --i) {
                    if (!isupper(rule[i])) {
                        break;
                    }
                    unsigned prev_size = follow[rule[i]].size();
                    follow[rule[i]].insert(follow[key_rules.first].begin(), follow[key_rules.first].end());
                    if (follow[rule[i]].size() > prev_size) {
                        change = true;
                    }
                    if (!nulls[rule[i]]) {
                        break;
                    }
                }
            }
        }
    }
}

void print_res(std::set<char> &non_t, MyMap mp)
{
    for (auto &nt : non_t) {
        std::cout << nt << ' ';
        for (auto &f : mp[nt]) {
            std::cout << f;
        }
        std::cout << std::endl;
    }
}

int main()
{
    std::vector<char> eps;
    std::string s;
    std::map<char, std::vector<std::string>> mp;
    std::map<char, int> nulls;
    std::set<char> non_t;
    while (std::getline(std::cin, s)) {
        nulls[s[0]] = -1;
        non_t.insert(s[0]);
        if (s.size() < 3) {
            eps.push_back(s[0]);
        } else {
            std::stringstream ss(s);
            char c;
            ss >> c >> s;
            mp[c].push_back(s);
        }
    }
    for (auto &e : eps) {
        nulls[e] = 1;
    }
    nullable(mp, nulls);
    for (auto &n_null : nulls) {
        if (n_null.second == -1) {
            n_null.second = 0;
        }
        std::cout << n_null.first << ' ' << n_null.second << std::endl;
    }

    MyMap mfirst;
    firsts(mp, mfirst, nulls);
    print_res(non_t, mfirst);

    MyMap follow;
    follows(mp, mfirst, nulls, follow);
    print_res(non_t, follow);

    return 0;
}
