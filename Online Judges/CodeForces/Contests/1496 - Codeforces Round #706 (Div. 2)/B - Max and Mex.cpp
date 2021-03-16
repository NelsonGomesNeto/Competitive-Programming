#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 1e5; int n; lli k;
lli a[maxN];

int main()
{
  int t; scanf("%d", &t);
  for (int tt = 1; tt <= t; tt++)
  {
    scanf("%d %lld", &n, &k);
    for (int i = 0; i < n; i++)
      scanf("%lld", &a[i]);

    // find mex
    map<lli, int> cnt;
    for (int i = 0; i < n; i++)
    {
      if (!cnt.count(a[i]))
        cnt[a[i]] = 0;
      cnt[a[i]]++;
    }
    lli mex = 0;
    for (auto &p: cnt)
      if (p.first > mex)
        break;
      else
        mex++;
    lli maximimum = cnt.rbegin()->first;

    lli ans = 0;
    if (mex > maximimum)
      ans = n + k;
    else
      ans = n + (k > 0) - cnt.count(((mex + maximimum) >> 1) + ((mex + maximimum) & 1));

    printf("%lld\n", ans);
  }
  return 0;
}
