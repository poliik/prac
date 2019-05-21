#include <iostream>
#include <string>
#include <sstream>
#include <map>

int main()
{
    std::string in;
    std::getline(std::cin, in);
    std::stringstream ss(in);
    std::map<std::string, int> mp;
    std::string s;
    int i = 1;
    while (ss >> s) {
        if (*(s.end() - 1) == ':' && (s.begin() + 1 != s.end())) {
            s.resize(s.size() - 1);
            mp[s] = i;
        } else {
            ++i;
        }
    }

    std::stringstream ss1(in);
    while (ss1 >> s) {
        if (*(s.end() - 1) != ':') {
            auto it = mp.find(s);
            if (it != mp.end()) {
                std::cout << it->second << std::endl;
            } else {
                std::cout << s << std::endl;
            }
        } else if (s.begin() + 1 == s.end()) {
            std::cout << s << std::endl;
        }
    }
    return 0;
}
