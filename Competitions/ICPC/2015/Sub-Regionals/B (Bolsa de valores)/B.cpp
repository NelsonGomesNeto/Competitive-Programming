#include <bits/stdc++.h>
using namespace std;

const int maxN = 2e5; int n, c;
int p[maxN];

int memo[maxN][2];
int solve(int i = 0, bool got = false)
{
  if (i == n) return(0);
  if (memo[i][got] == -1)
  {
    int ans = solve(i + 1, got);
    if (!got) ans = max(ans, solve(i + 1, true) - p[i] - c);
    if (got) ans = max(ans, p[i] + solve(i + 1, false));
    memo[i][got] = ans;
  }
  return(memo[i][got]);
}

int main()
{
  scanf("%d %d", &n, &c);
  for (int i = 0; i < n; i ++) scanf("%d", &p[i]);

  memset(memo, -1, sizeof(memo));
  int ans = solve();
  printf("%d\n", ans);

  return(0);
}