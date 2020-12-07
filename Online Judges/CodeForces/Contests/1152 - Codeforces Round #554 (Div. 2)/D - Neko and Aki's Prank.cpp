#include <bits/stdc++.h>
#define lli long long int
using namespace std;

const lli mod = 1e9 + 7;
const int maxN = 2e3; int n;
char ss[maxN + 1];
int depth = 0;

lli memo[maxN][maxN >> 1][2];
lli solve(int i = 0, int s = 0, bool selected = false)
{
  if (i == n) return(0);

  if (memo[i][s][selected] == -1)
  {
    lli ans = 0;
    if (selected)
    {
      if (s)
        ans = (ans + solve(i + 1, s - 1, false)) % mod;
      if (n - i > s + 1)
        ans = (ans + solve(i + 1, s + 1, false)) % mod;
    }
    else
    {
      if (s && n - i > s + 1)
        ans = (ans + max({(solve(i + 1, s - 1, false) + solve(i + 1, s + 1, false)) % mod,
                          (1 + solve(i + 1, s - 1, true) + solve(i + 1, s + 1, false)) % mod,
                          (solve(i + 1, s - 1, false) + 1 + solve(i + 1, s + 1, true)) % mod})) % mod;
      else
      {
        if (s)
          ans = (ans + max(solve(i + 1, s - 1, false), 1 + solve(i + 1, s - 1, true))) % mod;
        if (n - i > s + 1)
          ans = (ans + max(solve(i + 1, s + 1, false), 1 + solve(i + 1, s + 1, true))) % mod;
      }
    }
    memo[i][s][selected] = ans;
  }
  
  return(memo[i][s][selected]);
}

int main()
{
  scanf("%d", &n); n *= 2;

  memset(memo, -1, sizeof(memo));
  lli ans = solve();
  printf("%lld\n", ans);
  return(0);
}