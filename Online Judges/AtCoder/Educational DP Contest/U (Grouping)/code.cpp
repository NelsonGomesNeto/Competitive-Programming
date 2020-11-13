#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 16, maxMask = 1 << 16; int n, fullMask;
lli a[maxN][maxN];
lli groupSum[maxMask];

lli memo[maxMask];
lli solve(int bitmask = 0)
{
  if (bitmask == fullMask) return 0;
  lli &ans = memo[bitmask];
  if (ans != -1) return ans;

  for (int mask = 1; mask <= fullMask; mask++)
    if (!(mask & bitmask))
      ans = max(ans, groupSum[mask] + solve(mask | bitmask));

  return ans;
}

int main()
{
  while (scanf("%d", &n) != EOF)
  {
    fullMask = (1 << n) - 1;
    for (int i = 0; i < n; i++)
      for (int j = 0; j < n; j++)
        scanf("%lld", &a[i][j]);

    for (int bitmask = 0; bitmask <= fullMask; bitmask++)
    {
      lli sum = 0;
      for (int i = 0; i < n; i++)
        if (bitmask & (1 << i))
          for (int j = i + 1; j < n; j++)
            if (bitmask & (1 << j))
              sum += a[i][j];
      groupSum[bitmask] = sum;
    }

    memset(memo, -1, sizeof(memo));
    lli ans = solve();
    printf("%lld\n", ans);
  }
  return 0;
}