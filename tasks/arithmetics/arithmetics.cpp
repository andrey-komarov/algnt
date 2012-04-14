#include <fstream>
#include <iostream>
#include <cassert>

#include <gmpxx.h>

using namespace std;

int main()
{
#ifdef STDIO
    istream& in(cin);
    ostream& out(cout);
#else
    ifstream in("arithmetics.in");
    ofstream out("arithmetics.out");
#endif
    size_t n;
    in >> n;
    for (size_t i = 0; i < n; i++)
    {
        char op;
        mpz_class a, b;
        in >> op >> a >> b;
        if (op == '+')
            cout << a + b << "\n";
        else if (op == '-')
            cout << a - b << "\n";
        else if (op == '*')
            cout << a * b << "\n";
        else if (op == '/')
            cout << a / b << " " << a % b << "\n";
        else
            assert (op == '+' || op == '-' || op == '*' || op == '/');
    }
}
