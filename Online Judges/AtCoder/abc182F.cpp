#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 50; int n; lli x;
lli a[maxN];
bool used[maxN];

bool possible(lli y)
{
  memset(used, false, sizeof(used));

  lli yy = y, ch = y - x;
  for (int i = n - 1; yy;)
  {
    if (a[i] <= yy) yy %= a[i], used[i] = true;
    else i--;
  }

  lli best = 0;
  ch = y - x;
  for (int i = n - 1; ch;)
  {
    if (a[i] <= ch)
    {
      best += ch / a[i];
      ch %= a[i];
    }
    else i--;
  }

  lli needed = 0;
  ch = y - x;
  for (int i = n - 1; ch && i >= 0;)
  {
    if (a[i] <= ch && !used[i])
    {
      needed += ch / a[i];
      ch %= a[i];
    }
    else i--;
  }

  DEBUG printf("%lld %lld - %lld %lld\n", y, y - x, best, needed);

  return best == needed && ch == 0;
}

set<lli> visited;
map<pair<lli, lli>, lli> memo[maxN];
lli solve(int i = n - 1, lli curr = 0, lli change = 0)
{
  if (i < 0)
  {
    if (visited.count(curr + change)) return 0;
    visited.insert(curr + change);
    // printf("%lld %lld || %lld %lld\n", curr, change, curr + change, curr + change - x);
    return possible(curr + change);
  }
  pair<lli, lli> u = {curr, change};
  if (memo[i].count(u)) return memo[i][u];

  lli ans = 0;
  lli required = x >= curr ? (x - curr) / a[i] : 0;
  if (required == 0)
  {
    ans += solve(i - 1, curr, change);
    for (int j = 2, end = (i == n - 1 ? 1 : a[i + 1] / a[i]); j <= end; j++)
      ans += solve(i - 1, curr, change + j*a[i]);
    ans += solve(i - 1, curr + a[i], change);
  }
  else
  {
    ans += solve(i - 1, curr + required*a[i], change);
    ans += solve(i - 1, curr + (required + 1)*a[i], change);
  }

  return memo[i][u] = ans;
}

int main()
{
  while (scanf("%d %lld", &n, &x) != EOF)
  {
    for (int i = 0; i < n; i++)
      scanf("%lld", &a[i]);

    visited.clear();
    for (int i = 0; i < n; i++) memo[i].clear();
    lli ans = solve();
    printf("%lld\n", ans);
  }
  return 0;
}