#include <fstream>
#include <iostream>
#include <cassert>

#include <gmpxx.h>

using namespace std;

mpz_class egcd(const mpz_class& a, const mpz_class& b, mpz_class& x, mpz_class& y)
{
    if (b == 0)
    {
        x = 1;
        y = 0;
        return a;
    }
    const mpz_class& g = egcd(b, a % b, x, y);
    x -= a / b * y;
    swap(x, y);
    return g;
}

int main()
{
#ifdef STDIO
    istream& in(cin);
    ostream& out(cout);
#else
    ifstream in("egcd.in");
    ofstream out("egcd.out");
#endif
    mpz_class a, b;
    in >> a >> b;
    mpz_class x, y;
    mpz_class g = egcd(a, b, x, y);
    out << g << "\n" << x << "\n" << y << "\n";
}
