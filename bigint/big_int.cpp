#ifndef big_intCPP
#define big_intCPP
#include "big_int.h"

big_int::big_int(int b): 
    negative(false), 
    a(container(1)), 
    len(1)
{
    a[0] = b;
    normalize();
}

big_int::big_int(const container& b, size_t l): 
    negative(false), 
    len(l), 
    a(b)
{
    normalize();
}

big_int::big_int(const big_int& other): 
    a(other.a), 
    len(other.len), 
    negative(other.negative)
{
}

big_int::big_int(std::string s)
{    
    bool neg = false;
    if (s[0] == '-') 
    {
        neg = true;
        s = s.substr(1, s.size() - 1);
    }
    size_t n = s.size();
    size_t m = (n - 1) / big_int::base_length + 1;
    a = container(m);
    for (int i = n - 1, j = 0; i >= 0; i -= big_int::base_length, j++)
        if (i >= static_cast<int>(big_int::base_length))
            a[j] = atol(s.substr(i - big_int::base_length + 1, big_int::base_length).c_str());
        else
            a[j] = atol(s.substr(0, i + 1).c_str());
    *this = big_int(a, m);
    negative = neg;
}

void big_int::swap(big_int& b)
{
    a.swap(b.a);
    std::swap(len, b.len);
    std::swap(negative, b.negative);
}

big_int abs(big_int a)
{
    a.negative = false;
    return a;
}

bool big_int::operator==(const big_int& b) const
{
    if (len != b.len || negative != b.negative)
        return false;
    for (size_t i = 0; i < len; i++)
        if (a[i] != b.a[i])
            return false;
    return true;
}

bool big_int::operator>(const big_int& b) const
{
    if (negative != b.negative)
        return !negative;
    if (negative)
        return abs(*this) < abs(b);
    if (len != b.len)
        return len > b.len;
    for (int i = len - 1; i >= 0; i--)
        if (a[i] != b.a[i])
            return (a[i] > b.a[i]);
    return false;
}

bool operator<(const big_int& a, const big_int& b)
{
    return b > a;
}

bool operator<=(const big_int& a, const big_int& b)
{
    return !(a > b);
}

bool operator>=(const big_int& a, const big_int& b)
{
    return !(b > a);
}

bool operator!=(const big_int& a, const big_int& b)
{
    return !(a == b);
}

std::istream& operator>>(std::istream& is, big_int& val)
{
    std::string s;
    container a;
    
    while (!is.eof() && isspace(is.peek()))
        is.get();
    if (is.peek() == '+')
        is.get();
    else if (is.peek() == '-')
        s.push_back(static_cast<char>(is.get()));
    
    if (is.eof()) 
    {
        return is;
    }
    
    if (!isdigit(is.peek())) 
    {
        is.seekg(0, std::ios::end);
        is.setstate(std::ios::failbit);
        return is;
    }
    
    while (!is.eof() && isdigit(is.peek()))
        s.push_back(static_cast<char>(is.get()));
    
    val = big_int(s);
    return is;
}

std::ostream& operator<<(std::ostream& os, const big_int& val)
{
    int n = val.len;
    if (val.negative)
        os << "-";
    os << val.a[n - 1];
    for (int i = n - 2; i >= 0; i--)
    {
        digit_t now = val.a[i];
        digit_t now2 = now;
        int len = 0;
        for (len = 0; now2 > 9; now2 /= 10)
            len++;
        for (size_t i = 0; i < big_int::base_length - len - 1; i++)
            os << "0";
        os << now;
    }
    return os;
}

void big_int::normalize(container& a, size_t& l)
{
    bool expand = false;
    for (size_t i = 0; i < l; i++)
    {
        if (a[i] < 0) {
            a[i] += base;
            a[i + 1]--;
            expand |= i == l - 1;
        }        
        else if (a[i] >= base)
        {
            a[i + 1] += a[i] / base;
            a[i] %= base;
            expand |= i == l - 1;
        }
    }
    l += expand ? 1 : 0;
    while (a[l - 1] == 0 && l > 1)
        l--;
}

void big_int::normalize()
{
    normalize(a, len);
    if (a[len - 1] < 0) {
        negative = !negative;
        for (size_t i = 0; i < len; i++)
            a[i] = -a[i];
        normalize();
    }
    if (len == 1 && a[0] == 0)
        negative = false;
}

big_int& big_int::operator+=(const big_int& b)
{
    len = std::max(len, b.len);
    for (size_t i = 0; i < len; i++) {
        a[i] = a[i] * (negative ? -1 : 1) + b.a[i] * (b.negative ? -1 : 1);
    }
    negative = false;
    normalize();
    return *this;
}

big_int operator+(big_int a, const big_int& b)
{
    return a += b;
}

big_int operator-(big_int a)
{
    a.negative ^= true;
    a.normalize();
    return a;
}

big_int& operator-=(big_int& a, const big_int& b)
{
    return a += -b;
}

big_int operator-(big_int a, const big_int& b)
{
    return a -= b;
}

big_int& big_int::operator*=(const digit_t& b)
{
    for (size_t i = 0; i < len; i++)
        a[i] *= b;
    normalize();
    return *this;
}

big_int operator*(big_int a, const digit_t& b)
{
    return a *= b;
}

big_int& big_int::operator*=(const big_int& b)
{
    size_t l = len + b.len;
    bool sign = negative ^ b.negative;
    container res = container(l);
    for (size_t i = 0; i < l; i++)
        res[i] = 0;
    long long iterations_before_update = std::numeric_limits<digit_t>::max() / (base * base);
    for (size_t i = 0; i < len; i++)
    {
        for (size_t j = 0; j < b.len; j++)
            res[i + j] += a[i] * b.a[j];
        size_t tmp = l;
        if (static_cast<long long>(i) % iterations_before_update == 0)
            normalize(res, tmp);
    }
    big_int a(res, l);
    std::swap(a, *this);
    negative = sign;
    normalize();
    return *this;
}

big_int operator*(big_int a, const big_int& b)
{
    return a *= b;
}

big_int& big_int::operator/=(const digit_t& b)
{
    for (int i = len - 1; i >= 1; i--)
    {
        a[i - 1] += (a[i] % b) * base;
        a[i] /= b;
    }
    a[0] /= b;
    normalize();
    return *this;
}

big_int operator/(big_int a, const digit_t& b)
{
    return a /= b;
}

big_int big_int::operator<<(const size_t shift) const
{
    size_t l = len + shift;
    container b = container(l);
    for (size_t i = 0; i < l; i++)
        b[i] = 0;
    for(size_t i = 0; i < len; i++)
        b[i + shift] = a[i];
    normalize(b, l);
    return big_int(b, l);
}

big_int& big_int::operator/=(big_int b)
{
    if (b == 0)
        throw std::runtime_error("division by zero");
    bool sign = negative ^ b.negative;
    *this = abs(*this);
    b = abs(b);
    if (*this < b)
        return *this = 0;
    size_t lenN = len - b.len + 2;
    container c(lenN);
    if (b.a[b.len - 1] < base / 2)
    {
        digit_t qq = base / (b.a[b.len - 1] + 1);
        (*this) *= qq;
        b *= qq;
    }
    for (int pos = len - 1; pos >= 0; pos--)
    {
        if (len == 1)
        {
            if((*this) > b)
            {
                c[0] += a[0] / b.a[0];
                a[0] -= c[0] * b.a[0];
            }
            break;
        }
        size_t tmp = len - 1;
        digit_t good = 0;
        digit_t cc = (base * a[tmp] + a[tmp - 1]) / b.a[b.len - 1];
        digit_t l = std::max(cc - 2, 0LL);
        digit_t r = cc + 2;
        for (digit_t j = l; j <= r; j++) {
            if( ((b * j) << pos) <= (*this))
                good = j;
        }
        c[pos] += good;
        (*this) -= ((b * good) << pos);
    }
    if((*this) >= b && (*this) < b * 2)
        c[0]++;
    normalize(c, lenN);
    *this = big_int(c, lenN);
    negative = sign;
    return *this;
}

big_int operator/(big_int a, const big_int& b)
{
    return a /= b;
}

big_int& big_int::operator%=(const big_int& b)
{
    return (*this) -= (*this) / b * b;
}

big_int operator%(big_int a, const big_int& b)
{
    return a %= b;
}

#endif
