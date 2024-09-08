#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 1e5 + 1; int n;
lli s[maxN + 1];

map<int, int> memo[maxN];
int solve(int i = 1, int prv = -1)
{
  if (i >= n + 1) return 0;
  if (memo[i].count(prv)) return memo[i][prv];
  int ans = solve(i + (prv == -1 ? 1 : prv), prv);
  if (prv == -1 || (i % prv == 0 && s[i] > s[prv]))
    ans = max(ans, 1 + solve(i + i, i));
  return memo[i][prv] = ans;
}

int main()
{
  int t; scanf("%d", &t);
  while (t--)
  {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) scanf("%lld", &s[i]), memo[i].clear();

    int ans = solve();
    printf("%d\n", ans);
  }
  return 0;
}
