#include <iostream>
#include <array>
#include <thread>
#include <mutex>
#include <vector>
constexpr int CNT = 3;
constexpr int ITER = 1000000;
constexpr int DIFF = 100;
std::array<double, CNT> ar;
std::mutex m;

int main()
{
    std::vector<std::thread> threads;
    for (int i = 0; i < CNT; ++i) {
        threads.emplace_back([](int i) {
            for (int j = 0; j < ITER; ++j) {
                m.lock();
                ar[i] += DIFF * (i + 1);
                ar[(i + 1) % CNT] -= DIFF * (i + 1)+ 1;
                m.unlock();
            }
        }, i);
    }
    for (auto &t : threads) {
        t.join();
    }
    for (auto &x : ar) {
        printf("%.10g ", x);
    }
    return 0;
}
