#include <cmath>
#include <string>
namespace numbers
{
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
            if (buf) {
                delete [] buf;
            }
        }

        complex_stack(const complex_stack &st) : sz(st.sz), cap(st.cap), buf(new complex[st.cap])
        {
            st.copy(buf);
        }

        complex_stack(complex_stack &&st) : sz(st.sz), cap(st.cap), buf(st.buf)
        {
            st.buf = nullptr;
        }

        complex_stack &operator =(const complex_stack &st)
        {
            if (st.sz > cap) {
                resize(st.sz + 1);
            }
            sz = st.sz;
            st.copy(buf);
            return *this;
        }

        complex_stack &operator =(complex_stack &&st)
        {
            if (buf) {
                delete [] buf;
            }
            buf = st.buf;
            sz = st.sz;
            cap = st.cap;
            st.buf = nullptr;
            return *this;
        }

        void resize(size_t new_cap) {
            cap = new_cap;
            buf = static_cast<complex *>(operator new[] (cap * sizeof(complex)));
        }

        size_t size() const
        {
            return sz;
        }

        complex &operator [](size_t i)
        {
            return buf[i];
        }

        complex operator [](size_t i) const
        {
            return buf[i];
        }

        friend complex_stack operator <<(const complex_stack &cs, complex x);
        friend complex_stack operator <<(complex_stack &&cs, complex x);
        friend complex_stack operator ~(const complex_stack &st);
        friend complex_stack operator ~(complex_stack &&st);

        complex operator +() const
        {
            return buf[sz - 1];
        }

    };
    complex_stack operator ~(const complex_stack &st)
    {
        complex_stack tmp(st);
        --tmp.sz;
        return tmp;
    }
    complex_stack operator ~(complex_stack &&st)
    {
        complex_stack tmp(std::move(st));
        --tmp.sz;
        return tmp;
    }
    complex_stack operator <<(const complex_stack &st, complex x)
    {
        complex_stack tmp(st);
        if (tmp.cap == tmp.sz) {
            tmp.resize(tmp.cap * k);
        }
        tmp.buf[tmp.sz++] = x;
        return tmp;
    }
    complex_stack operator <<(complex_stack &&st, complex x)
    {
        complex_stack tmp(std::move(st));
        if (tmp.cap == tmp.sz) {
            tmp.resize(tmp.cap * k);
        }
        tmp.buf[tmp.sz++] = x;
        return tmp;
    }
}
