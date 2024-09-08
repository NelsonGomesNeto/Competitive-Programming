#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 100;
char ss[maxN + 1];

int main()
{
  while (~scanf(" %s", ss))
  {
    string s = string(ss);
    for (int i = 0; i < s.size(); i += 2)
      swap(s[i], s[i + 1]);
    printf("%s\n", s.c_str());
  }
  return 0;
}
