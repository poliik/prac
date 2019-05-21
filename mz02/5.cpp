#include <iostream>
using namespace std;

class S
{
    int sum;
    bool is_empty, flag;
public:
    S() : sum(0), is_empty(true), flag(true)
    {
        if (cin >> sum) {
            is_empty = false;
        } else {
            flag = false;
        }
    }

    S(S&& moved)
        : sum(moved.sum)
        , is_empty(moved.is_empty)
        , flag(moved.flag)
    {
        int x;
        if (cin >> x) {
            sum += x;
        } else {
            flag = false;
        }
    }

    ~S()
    {
        if (!is_empty && !flag) {
            cout << sum << ' ';
        }
    }

    explicit operator bool()
    {
        return flag;
    }
};
