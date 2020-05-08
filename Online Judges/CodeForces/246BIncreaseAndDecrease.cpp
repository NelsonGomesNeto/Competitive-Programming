#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 1e5, maxA = 2e4; int n;
int a[maxN];
int cnt[maxA + 1];
lli l[maxA + 1], r[maxA + 1];

int main()
{
  int n;
  while (scanf("%d", &n) != EOF)
  {
    memset(cnt, 0, sizeof(cnt));
    for (int i = 0; i < n; i++)
    {
      scanf("%d", &a[i]); a[i] += (maxA>>1);
      cnt[a[i]]++;
    }

    for (int x = 1, s = cnt[0]; x <= maxA; x++)
    {
      l[x] = l[x - 1] + s;
      s += cnt[x];
    }
    for (int x = maxA - 1, s = cnt[maxA]; x >= 0; x--)
    {
      r[x] = r[x + 1] + s;
      s += cnt[x];
    }

    int ans = n - 1;
    for (int x = 0; x <= maxA; x++)
    {
      DEBUG
        if (l[x] && r[x])
          printf("%d %lld %lld\n", x, l[x], r[x]);
      if (l[x] == r[x])
        ans = n;
    }
    printf("%d\n", ans);
  }
  return 0;
}