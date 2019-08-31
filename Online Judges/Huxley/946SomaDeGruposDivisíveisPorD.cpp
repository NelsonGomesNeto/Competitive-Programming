#include <bits/stdc++.h>
#define lli long long int
using namespace std;

const int maxN = 200, maxM = 10, maxD = 20; int n, q, d, m;
int a[maxN];

int memo[maxN][maxM + 1][maxD];
int solve(int i = 0, int amount = 0, int rem = 0)
{
  if (i == n) return amount == m && rem == 0;
  if (memo[i][amount][rem] == -1)
  {
    int ans = solve(i + 1, amount, rem);
    if (amount < m) ans += solve(i + 1, amount + 1, (((rem + a[i]) % d) + d) % d);
    memo[i][amount][rem] = ans;
  }
  return memo[i][amount][rem];
}

int main()
{
  int t = 1;
  while (scanf("%d %d", &n, &q) && !(!n && !q))
  {
    for (int i = 0; i < n; i ++) scanf("%d", &a[i]);
    printf("SET %d:\n", t ++);
    for (int qq = 1; qq <= q; qq++)
    {
      scanf("%d %d", &d, &m);
      memset(memo, -1, sizeof(memo));
      int ans = solve();
      printf("QUERY %d: %d\n", qq, ans);
    }
  }
  return(0);
}