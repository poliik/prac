#include <iostream>
#include <thread>
#include <vector>
#include <exception>
#include <future>

bool prime(uint64_t n)
{
    if (n == 1) {
        return false;
    }
    for (uint64_t i = 2; i * i <= n; ++i) {
        if (!(n % i)) {
        return false;
        }
    }
    return true;
}

int main()
{
    uint64_t low, high;
    uint32_t cnt;
    std::cin >> low >> high >> cnt;
    std::vector<std::promise<uint64_t>> promises(cnt);
    std::vector<std::future<uint64_t>> futures(cnt);
    for (uint32_t i = 0; i < cnt; ++i) {
        futures[i] = promises[i].get_future();
    }
    std::thread thr([](uint64_t low, uint64_t high, uint32_t cnt,
        std::vector<std::promise<uint64_t>> &promises) {
        uint32_t n = 0;
        for (; low <= high; ++low) {
            if (prime(low)) {
                promises[n++].set_value(low);
            }
            if (n == cnt) {
                return;
            }
        }
        promises[n].set_exception(std::make_exception_ptr(high));
    }, low, high, cnt, std::ref(promises));

    try {
        for (auto &f : futures) {
            std::cout << f.get() << std::endl;
        }
    } catch (const uint64_t &e) {
        std::cout << e << std::endl;
    }

    thr.join();
    return 0;
}
