#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 3e5;
int n, m; lli k;
char ss[maxN + 1];
string s, t;

int main()
{
  while (~scanf("%d %d %lld", &n, &m, &k))
  {
    scanf(" %s", ss);
    s = string(ss);
    t = s + s;

    int totalXs = 0;
    for (char c : s) totalXs += c == 'x';

    lli additionalK = k - totalXs;

    int lo = 0, hi = 0, xs = 0;
    while (hi < t.size() && xs < k)
    {
      xs += t[hi] == 'x';
      ++hi;
    }
    while (hi + 1 < t.size() && t[hi + 1] == 'o')
      ++hi;
    auto getSize = [](int lo, int hi) { return hi - lo + 1; };
    int ans = 0;

    for (; hi < t.size(); ++hi)
    {
      if (t[hi] == 'x')
      {
        ++xs;

        while (hi + 1 < t.size() && t[hi + 1] == 'o')
          ++hi;

        while (lo < hi && xs > k)
        {
          xs -= t[lo] == 'x';
          ++lo;
        }
      }

      ans = max(ans, getSize(lo, hi));
    }

    printf("%d\n", ans);
  }
  return 0;
}
