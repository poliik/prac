#include <iostream>
#include <vector>
constexpr int SHIFT1 = 1;
constexpr int SHIFT2 = 3;

void beta(std::vector<int> &v1, std::vector<int> &v2, int len)
{
    if (!len) {
        for (auto &x : v1) {
            std::cout << x;
        }
        for (auto &x : v2) {
            std::cout << x;
        }
        std::cout << std::endl;
        return;
    }
    v2.push_back(SHIFT1);
    beta(v1, v2, len - 1);
    v2.pop_back();
    v2.push_back(SHIFT1 + 1);
    beta(v1, v2, len - 1);
    v2.pop_back();

}

void alpha(std::vector<int> &v1, std::vector<int> &v2, int len)
{
    if (!len) {
        for (auto &x : v1) {
            std::cout << x;
        }
        std::cout << std::endl;
        return;
    }
    beta(v1, v2, len);
    v1.push_back(SHIFT2);
    alpha(v1, v2, len - 1);
    v1.pop_back();
    v1.push_back(SHIFT2 + 1);
    alpha(v1, v2, len - 1);
    v1.pop_back();
}

int main()
{
    int k;
    std::cin >> k;
    std::vector<int> v1, v2;
    alpha(v1, v2, k);
    return 0;
}
