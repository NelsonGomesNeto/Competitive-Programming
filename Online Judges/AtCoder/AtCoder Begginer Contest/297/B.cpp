#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 8;
char ss[maxN + 1];
string s;

int main()
{
  while (~scanf(" %s", ss))
  {
    s = string(ss);

    bool ans = false;
    int firstB, lastB;
    for (int i = 0; i < s.size(); ++i)
      if (s[i] == 'B')
        lastB = i;
    for (int i = s.size() - 1; i >= 0; --i)
      if (s[i] == 'B')
        firstB = i;

    ans = (firstB & 1) != (lastB & 1);

    int firstR, lastR;
    for (int i = 0; i < s.size(); ++i)
      if (s[i] == 'R')
        lastR = i;
    for (int i = s.size() - 1; i >= 0; --i)
      if (s[i] == 'R')
        firstR = i;

    int k;
    for (int i = 0; i < s.size(); ++i)
      if (s[i] == 'K')
        k = i;

    ans &= firstR < k && k < lastR;
    printf("%s\n", ans ? "Yes" : "No");
  }
  return 0;
}
