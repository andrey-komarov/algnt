#include <fstream>
#include <iostream>

#include <gmpxx.h>

using namespace std;

int main()
{
#ifdef STDIO
    istream& in(cin);
    ostream& out(cout);
#else
    ifstream in("fibonacci1.in");
    ofstream out("fibonacci1.out");
#endif
    mpz_class a(1), b(1);
    size_t n;
    in >> n;
    for (size_t i = 1; i < n; i++)
    {
        mpz_class tmp = a + b;
        a = b;
        b = tmp;
    }
    out << a << "\n";
}
