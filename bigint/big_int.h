#ifndef big_intH
#define big_intH

#include <string>
#include <istream>
#include <ostream>

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
    big_int& operator%=(const digit_t&);
    
    digit_t to_int() const;

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
    friend digit_t operator%(big_int, const digit_t&);
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
digit_t operator%(big_int, const digit_t&);

#endif /* big_intH */
