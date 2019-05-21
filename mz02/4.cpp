#include <iostream>
#include <cmath>
#include <cstdlib>
namespace numbers
{
    class complex
    {
        double re, im;
    public:
        complex(double x = 0, double y = 0) : re(x), im(y) {};
        explicit complex(const char *s)
        {
            char *im_ptr;
            re = strtod(s + 1, &im_ptr);
            im = strtod(im_ptr + 1, nullptr);
        }
        double get_re() const
        {
            return re;
        }
        double get_im() const
        {
            return im;
        }
        double abs2() const
        {
            return re * re + im * im;
        }
        double abs() const
        {
            return sqrt(re * re + im * im);
        }
        void to_string(char *buf, size_t size) const
        {
            snprintf(buf, size, "(%.10g,%.10g)", re, im);
        }
        friend complex operator+(const complex &a, const complex &b);
        friend complex operator-(const complex &a, const complex &b);
        friend complex operator*(const complex &a, const complex &b);
        friend complex operator/(const complex &x, const complex &y);
        friend complex operator-(complex x);
        friend complex operator~(complex x);
    };
    complex operator+(const complex &a, const complex &b)
    {
        return complex(a.re + b.re, a.im + b.im);
    }
    complex operator-(const complex &a, const complex &b)
    {
        return complex(a.re - b.re, a.im - b.im);
    }
    complex operator*(const complex &a, const complex &b)
    {
        return complex(a.re * b.re - a.im * b.im,
                a.re * b.im + a.im  * b.re);
    }
    complex operator/(const complex &x, const complex &y)
    {
        complex tmp((x.re * y.re + x.im * y.im) / y.abs2(),
                (y.re * x.im - y.im * x.re) / y.abs2());
        return tmp;
    }
    complex operator-(complex x)
    {
        return complex(-x.re, -x.im);
    }
    complex operator~(complex x)
    {
        return complex(x.re, -x.im);
    }

    constexpr int MAX_SIZE = 500;
    constexpr int k = 2;
    class complex_stack
    {
        size_t sz;
        size_t cap;
        complex *buf;

        void copy(complex *new_buf) const
        {
            for (size_t i = 0; i < sz; ++i) {
                new_buf[i] = buf[i];
            }
        }

    public:
        complex_stack () : sz(0), cap(MAX_SIZE), buf(new complex[MAX_SIZE]) {};
        ~complex_stack()
        {
            delete [] buf;
        }

        complex_stack(const complex_stack &st) : sz(st.sz), cap(st.cap), buf(new complex[st.cap])
        {
            st.copy(buf);
        }

        complex* stack()
        {
            return buf;
        }

        complex_stack &operator=(const complex_stack &st)
        {
            if (st.sz > cap) {
                resize(st.sz + 1);
            }
            sz = st.sz;
            st.copy(buf);
            return *this;
        }

        void resize(size_t new_cap) {
            cap = new_cap;
            complex *new_buf = new complex[new_cap];
            copy(new_buf);
            delete [] buf;
            buf = new_buf;
        }

        size_t size() const
        {
            return sz;
        }

        complex &operator[](size_t i)
        {
            return buf[i];
        }

        complex operator[](size_t i) const
        {
            return buf[i];
        }

        friend complex_stack operator<<(const complex_stack &cs, complex x);

        complex operator+() const
        {
            return buf[sz - 1];
        }

        complex_stack &operator~()
        {
            --sz;
            return *this;
        }

    };

    complex_stack operator<<(const complex_stack &st, complex x)
    {
        complex_stack tmp(st);
        if (tmp.cap == tmp.sz) {
            tmp.resize(tmp.cap * k);
        }
        tmp.buf[tmp.sz++] = x;
        return tmp;
    }

    complex eval(char **args, const complex &z)
    {
        complex_stack st;
        for (int i = 0; args[i]; ++i) {
            if (args[i][0] == '(') {
                complex tmp(args[i]);
                st = st << tmp;
            } else if (args[i][0] == 'z') {
                st = st << z;
            } else if (args[i][0] == '+') {
                complex tmp = (+st);
                ~st;
                complex tmp2 = (+st);
                ~st;
                st = st << (tmp + tmp2);
            } else if (args[i][0] == '-') {
                complex tmp = (+st);
                ~st;
                complex tmp2 = (+st);
                ~st;
                st = st << (tmp2 - tmp);
            } else if (args[i][0] == '*') {
                complex tmp = (+st);
                ~st;
                complex tmp2 = (+st);
                ~st;
                st = st << (tmp * tmp2);
            } else if (args[i][0] == '/') {
                complex tmp = (+st);
                ~st;
                complex tmp2 = (+st);
                ~st;
                st = st << (tmp2 / tmp);
            } else if (args[i][0] == '!') {
                st = st << (+st);
            } else if (args[i][0] == ';') {
                ~st;
            } else if (args[i][0] == '~') {
                complex tmp = (+st);
                ~st;
                st = st << (~tmp);
            } else if (args[i][0] == '#') {
                complex tmp = (+st);
                ~st;
                st = st << (-tmp);
            }
        }
        return +st;
    }
}
using namespace numbers;

constexpr int SIZE = 300;
int main(int argc, char **argv)
{
    complex c(argv[1]);
    double r = strtod(argv[2], nullptr);
    int n = atoi(argv[3]);
    complex x, res;
    for (int i = 0; i < n; ++i) {
        double ang = i * 2 * M_PI / n;
        complex z1(r * cos(ang), r * sin(ang));
        complex tmp(eval(argv + 4, z1 + c));
        complex z2(-sin(ang) * r, cos(ang) * r);

        res = res + tmp * z2;
    }
    res = res * 2 * M_PI / n;
    char buf[SIZE];
    res.to_string(buf, SIZE);
    std::cout << buf << std::endl;
    return 0;
}
