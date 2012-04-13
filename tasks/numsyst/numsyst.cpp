#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>

#include "big_int.h"
#include "numsyst.h"

using namespace std;

int main()
{
#ifdef STDIO
    istream& in(cin);
    ostream& out(cout);
#else
    ifstream in("numsyst.in");
    ofstream out("numsyst.out");
#endif
    string s;
    in >> s;
    int b1, b2;
    in >> b1 >> b2;
    big_int a = decode(s, b1);
    string ans = encode(a, b2);
    out << ans << "\n";
}
