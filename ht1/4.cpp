#include <iostream>
#include <thread>
#include <vector>
#include <future>
#include <iomanip>

std::pair<unsigned long long, unsigned long long> f(unsigned i, unsigned long long iter)
{
    unsigned long long p_in = 0;
    for (unsigned long long k = 0; k < iter; ++k) {
        double x = (rand_r(&i) / (RAND_MAX + 1.0)) * 2 - 1;
        double y = (rand_r(&i) / (RAND_MAX + 1.0)) * 2 - 1;
        if (x * x + y * y <= 1.0) {
            ++p_in;
        }
    }
    return std::make_pair(p_in, iter);
}


int main(int argc, char **argv)
{
    unsigned long long cnt = atoll(argv[1]), iter = atoll(argv[2]);
    std::vector<std::future<std::pair<unsigned long long, unsigned long long>>> futures(cnt);
    for (unsigned long long i = 0; i < cnt; ++i) {
        futures[i] = std::async(std::launch::async, f, i, iter);
    }

    unsigned long long p_in = 0, p_out = 0;
    for (auto &p : futures) {
        auto res = p.get();
        p_in += res.first;
        p_out += res.second;
    }
    std::cout << std::setprecision(6) << 4.0 * p_in / p_out << std::endl;
    return 0;
}
