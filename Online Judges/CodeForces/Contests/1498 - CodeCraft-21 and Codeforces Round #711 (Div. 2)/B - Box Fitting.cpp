#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 1e5; int n; lli W;
lli w[maxN];
int cnt[64];

int main()
{
  int t; scanf("%d", &t);
  for (int tt = 1; tt <= t; tt++)
  {
    scanf("%d %lld", &n, &W);
    for (int i = 0; i < n; i++)
      scanf("%lld", &w[i]);

    memset(cnt, 0, sizeof(cnt));
    for (int i = 0; i < n; i++)
      for (int p = 0; p < 60; p++)
        if (w[i] == (1LL << p))
          cnt[p]++;

    int total = n;
    lli ans = 0, curr = 0;
    while (total)
    {
      for (int p = 59; p >= 0; p--)
      {
        lli sz = 1LL << p;
        while (cnt[p] && curr + sz <= W)
          cnt[p]--, total--, curr += sz;
      }
      ans++, curr = 0;
    }
    printf("%lld\n", ans);

  }
  return 0;
}