#include <thread>
#include <vector>
#include <future>

template<class Input, class Output, class Function, class Callback>
void async_vector(const std::vector<Input> ins, Function &&f, Callback &&c)
{
    std::thread thr([] (const std::vector<Input> ins, Function &&f, Callback &&c) {
        std::vector<std::future<Output>> futures;
        for (const auto &i : ins) {
            futures.emplace_back(std::async(std::launch::async, f, i));
        }
        std::vector<Output> res;
        for (auto &f : futures) {
            res.push_back(f.get());
        }
        const std::vector<Output> &rf = res;
        c(rf);
    }, ins, f, c);
    thr.detach();
}
