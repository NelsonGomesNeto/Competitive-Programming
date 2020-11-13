#include <bits/stdc++.h>
#define DEBUG if(1)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 3e3; int n;
const lli mod = 1e9 + 7;
char s[maxN + 1];

lli memo[maxN][maxN], pmemo[maxN][maxN], prefix[maxN][maxN + 1];
lli solve(int i, int nxt);
lli pref(int i, int nxt, int prv)
{
  if (prv < 0) return 0;
  lli &ans = pmemo[i][prv];
  if (ans != -1) return ans;
  return ans = (pref(i, nxt, prv - 1) + solve(i - 1, prv)) % mod;
}
lli solve(int i, int nxt)
{
  if (i == 0) return nxt == 0;
  lli &ans = memo[i][nxt];
  if (ans != -1) return ans;

  int lo, hi;
  if (s[i - 1] == '>')
    lo = nxt, hi = i - 1;
  else
    lo = 0, hi = nxt - 1;

  // ans = 0;
  // for (int prv = lo; prv <= hi; prv++)
  //   ans = (ans + solve(i - 1, prv)) % mod;
  ans = (pref(i, nxt, hi) - pref(i, nxt, lo - 1) + mod) % mod;

  return ans;
}
lli solve2()
{
  memset(memo, 0, sizeof(memo));
  memset(prefix, 0, sizeof(prefix));
  prefix[0][1] = 1;
 
  for (int i = 1; i < n; i++)
  {
    for (int nxt = 0; nxt <= i; nxt++)
    {
      int lo, hi;
      if (s[i - 1] == '>')
        lo = nxt, hi = i - 1;
      else
        lo = 0, hi = nxt - 1;
 
      // for (int prv = lo; prv <= hi; prv++)
        // memo[i][nxt] = (memo[i][nxt] + memo[i - 1][prv]) % mod;
      memo[i][nxt] = (memo[i][nxt] + prefix[i - 1][hi + 1] - prefix[i - 1][lo] + mod) % mod;
      prefix[i][nxt + 1] = (prefix[i][nxt] + memo[i][nxt]) % mod;
    }
  }
  lli ans = 0;
  for (int i = 0; i < n; i++)
    ans = (ans + memo[n - 1][i]) % mod;
  return ans;
}

int main()
{
  while (scanf("%d", &n) != EOF)
  {
    scanf(" %s", s);

    // lli ans = solve();
    lli ans = 0;
    memset(memo, -1, sizeof(memo));
    memset(pmemo, -1, sizeof(pmemo));
    for (int i = 0; i < n; i++)
      ans = (ans + solve(n - 1, i)) % mod;
    printf("%lld\n", ans);
  }
  return 0;
}