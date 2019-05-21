#include <thread>
template <typename T1, typename T2, typename ...ArgsT>
void async_launch(T1 &&f1, T2 &&f2, ArgsT &&...args)
{
    std::thread thr([](T1 &&f1, T2 &&f2, ArgsT &&...args) {
        auto res = f1(std::forward<ArgsT>(args)...);
        f2(std::forward<decltype(res)>(res));
    }, f1, f2, std::forward<ArgsT>(args)...);
    thr.detach();
}
