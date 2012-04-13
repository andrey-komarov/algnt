#include <fstream>
#include <iostream>
#include <vector>
#include <utility>

using namespace std;

int main()
{
#ifdef STDIO
    istream& in(cin);
    ostream& out(cout);
#else
    ifstream in("factor1.in");
    ofstream out("factor1.out");
#endif
    long long n;
    in >> n;
    vector<pair<long long, int> > divisors;
    for (long long i = 2; i * i <= n; i++)
    {
        if (n % i == 0)
        {
            int cnt = 0;
            while (n % i == 0)
            {
                n /= i;
                cnt++;
            }
            divisors.push_back({i, cnt});
        }
    }
    if (n != 1)
        divisors.push_back({n, 1});
    out << divisors.size() << "\n";
    for (auto it = divisors.begin(); it != divisors.end(); it++)
        out << it->first << " " << it->second << "\n";
}
