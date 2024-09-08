#include <bits/stdc++.h>
using namespace std;

const int maxN = 200;
const int mod = 1e9 + 7;
int n, m, k;

int memo[maxN][maxN + 1];
int solve(int i = 0, int rem = n)
{
  if (i == m) return rem == 0;
  int& ans = memo[i][rem];
  if (ans != -1) return ans;

  ans = 0;
  for (int j = 1, end = min(rem, k); j <= end; ++j)
    ans = (ans + solve(i + 1, rem - j)) % mod;

  return ans;
}

int main()
{
  while (~scanf("%d %d %d", &n, &m, &k))
  {
    memset(memo, -1, sizeof(memo));
    int ans = solve();
    printf("%d\n", ans);
  }
  return 0;
}