#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 21, maxBitmask = (1 << 21) + 1; int n;
const lli mod = 1e9 + 7;
int a[maxN][maxN];

lli memo[maxN][maxBitmask];
lli solve(int i = 0, int bitmask = 0)
{
  if (i == n) return 1;
  lli &ans = memo[i][bitmask];
  if (ans != -1) return ans;

  ans = 0;
  for (int j = 0; j < n; j++)
    if (a[i][j] && !(bitmask & (1 << j)))
      ans = (ans + solve(i + 1, bitmask | (1 << j))) % mod;
  return ans;
}

int main()
{
  while (scanf("%d", &n) != EOF)
  {
    for (int i = 0; i < n; i++)
      for (int j = 0; j < n; j++)
        scanf("%d", &a[i][j]);

    memset(memo, -1, sizeof(memo));
    lli ans = solve();
    printf("%lld\n", ans);
  }
  return 0;
}