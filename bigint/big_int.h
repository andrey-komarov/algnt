#ifndef big_intH
#define big_intH

#include <cstdlib>
#include <string>
#include <iostream>
#include <algorithm>
#include <stdexcept>
#include <limits>

#include "container.h"

struct big_int
{
    big_int(int = 0);
    big_int(const big_int&);
    big_int(std::string);
    void swap(big_int&);
    bool operator==(const big_int&) const;
    bool operator>(const big_int&) const;
    big_int& operator+=(const big_int&);
    big_int& operator*=(const digit_t&);
    big_int& operator*=(const big_int&);
    big_int& operator/=(const digit_t&);
    big_int& operator/=(big_int);
    big_int& operator%=(const big_int&);

private:
    static const digit_t base = 1000000000;
    static const size_t base_length = 9;

    container a;
    size_t len;
    bool negative;

    big_int(const container&, size_t);
    void normalize();
    static void normalize(container& a, size_t&);
    big_int operator<<(const size_t) const;

    friend std::istream& operator>>(std::istream&, big_int&);
    friend std::ostream& operator<<(std::ostream&, const big_int&);
    friend big_int operator-(big_int);
    friend big_int abs(big_int a);
};

big_int abs(big_int a);

bool operator<(const big_int&, const big_int&);
bool operator<=(const big_int&, const big_int&);
bool operator>=(const big_int&, const big_int&);
bool operator!=(const big_int&, const big_int&);

big_int& operator-=(big_int&, const big_int&);
big_int operator-(big_int, const big_int&);
big_int operator+(big_int, const big_int&);
big_int operator*(big_int, const digit_t&);
big_int operator*(big_int, const big_int &);
big_int operator/(big_int, const digit_t&);
big_int operator/(big_int, const big_int&);
big_int operator%(big_int, const big_int&);

#endif /* big_intH */
