#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 400; int n, m;
const lli mod = 998244353;
bool good[maxN][maxN];

/*
  This won't work because you may start enqueueing after removing, example:

  1 2 3 4 5 6

  skip 1
  merge 2 and 3
  skip 4

  now you have this queue: [1, 4] to process :/


  
*/
lli memo[maxN + 1][maxN + 1][maxN];
lli solve(int start = 0, int rem = -1, int i = 0)
{
  DEBUG printf("\t%d %d %d\n", start, rem, i);
  if (i == n) return rem < start;
  lli &ans = memo[start + 1][rem + 1][i];
  if (ans != -1) return ans;

  ans = 0;
  if (i + 1 < n && good[i][i + 1])
    ans = (ans + solve(start, rem, i + 2)) % mod;

  // add to remaining
  if (rem < start)
    ans = (ans + solve(i, i, i + 1)) % mod;
  else
    ans = (ans + solve(start, i, i + 1)) % mod; // add to remaining

  // clear remaining
  if (rem >= start && good[rem][i])
    ans = (ans + solve(start, rem - 1, i + 1)) % mod;

  return ans;
}

int main()
{
  while (~scanf("%d %d", &n, &m))
  {
    n *= 2;
    memset(good, false, sizeof(good));
    for (int i = 0; i < m; i++)
    {
      int a, b; scanf("%d %d", &a, &b); a--, b--;
      good[a][b] = good[b][a] = true;
    }

    memset(memo, -1, sizeof(memo));
    lli ans = solve();
    printf("%lld\n", ans);
  }
  return 0;
}