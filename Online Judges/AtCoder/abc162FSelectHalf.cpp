#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 2e5; int n;
lli a[maxN];

lli memo[maxN][3];
lli solve(int i = 0, int jumps = n & 1 ? 2 : 1)
{
  if (i >= n) return 0;
  if (memo[i][jumps] != -1) return memo[i][jumps];

  lli ans = a[i] + solve(i + 2, jumps);
  if (jumps) ans = max(ans, solve(i + 1, jumps - 1));
  return memo[i][jumps] = ans;
}

int main()
{
  while (scanf("%d", &n) != EOF)
  {
    for (int i = 0; i < n; i++)
      scanf("%lld", &a[i]);

    memset(memo, -1, sizeof(memo));
    lli ans = solve();
    printf("%lld\n", ans);
  }
  return 0;
}