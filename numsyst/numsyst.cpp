#include "numsyst.h"

#include <cassert>
#include <algorithm>

char itoletter(int a)
{
    if (0 <= a && a <= 9)
        return '0' + a;
    if (10 <= a && a <= 36)
        return 'A' + a - 10;
    assert (false);
}

int lettertoi(char ch)
{
    if ('0' <= ch && ch <= '9')
        return ch - '0';
    if ('A' <= ch && ch <= 'Z')
        return ch + 10 - 'A';
    assert (false);
}

std::string encode(mpz_class a, size_t base)
{
    std::string s;
    while (a != 0)
    {
        mpz_class now = a % base;
        s += itoletter(now.get_si());
        a /= base;
    }
    std::reverse(s.begin(), s.end());
    return s;
}

mpz_class decode(const std::string& s, size_t base)
{
    mpz_class ans = 0;
    for (auto it = s.begin(); it != s.end(); it++)
        ans = ans * base + lettertoi(*it);
    return ans;
}
