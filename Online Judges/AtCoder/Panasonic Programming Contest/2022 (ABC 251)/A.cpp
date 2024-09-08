#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 3;
char ss[maxN + 1];

int main()
{
  while (~scanf(" %s", ss))
  {
    string s;
    while (s.size() < 6) s += string(ss);
    printf("%s\n", s.c_str());
  }
  return 0;
}
