#include <iostream>
#include <array>
#include <thread>
#include <mutex>
#include <vector>
#include <iomanip>

void f(unsigned iter, unsigned id1, unsigned id2, double sum1, double sum2,
    std::vector<double> &accs, std::vector<std::mutex> &mutexes)
{
    for (unsigned j = 0; j < iter; ++j) {
        unsigned n1 = std::min(id1, id2);
        unsigned n2 = std::max(id1, id2);
        std::unique_lock<std::mutex> w1(mutexes[n1]);
        std::unique_lock<std::mutex> w2(mutexes[n2]);
        accs[id1] += sum1;
        accs[id2] += sum2;
    }
}

int main()
{
    unsigned acc_count, thr_count;
    std::cin >> acc_count >> thr_count;
    std::vector<std::thread> threads;
    std::vector<double> accs(acc_count, 0.0);
    std::vector<std::mutex> mutexes(acc_count);
    for (unsigned i = 0; i < thr_count; ++i) {
        unsigned iter, id1, id2;
        double sum1, sum2;
        std::cin >> iter >> id1 >> sum1 >> id2 >> sum2;
        threads.emplace_back(f, iter, id1, id2, sum1, sum2, std::ref(accs), std::ref(mutexes));
    }
    for (auto &t : threads) {
        t.join();
    }
    for (auto &x : accs) {
        std::cout << std::setprecision(10) << x << std::endl;
    }
    return 0;
}
