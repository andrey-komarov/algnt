#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>

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
    string ans = encode(decode(s, b1), b2);
    out << ans << "\n";
}
