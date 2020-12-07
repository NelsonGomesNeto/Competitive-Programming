#include <bits/stdc++.h>
#define DEBUG if(1)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 1e5; int n;
pair<vector<bool>, lli> aa[maxN];
lli a[maxN];

int findFirstOne(int at, int lo, int hi)
{
  at = 29 - at;
  while (lo < hi)
  {
    int mid = (lo + hi) >> 1;
    if (aa[mid].first[at]) hi = mid;
    else lo = mid + 1;
  }
  return !aa[lo].first[at] ? lo + 1 : lo;
}

lli memo[30][maxN][2];
lli solve(lli at = 29, int lo = 0, int hi = n - 1, bool chosen = false)
{
  if (at == -1) return 0;
  if (memo[at][lo][chosen] != -1) return memo[at][lo][chosen];

  int fo = findFirstOne(at, lo, hi);
  if (fo == lo || fo == hi + 1)
    return solve(at - 1, lo, hi, false);

  lli ans = (1LL << at) | min(solve(at - 1, lo, fo - 1, false), solve(at - 1, fo, hi, true));
  return memo[at][lo][chosen] = ans;
}

int main()
{
  while (scanf("%d", &n) != EOF)
  {
    for (int i = 0; i < n; i ++)
    {
      scanf("%lld", &a[i]);
      aa[i].first = vector<bool>(30);
      // for (int j = 0; j < 30; j ++)
      for (int j = 29, jj = 0; j >= 0; j --, jj ++)
        aa[i].first[jj] = (a[i] & (1LL << j)) != 0;
    }
    sort(aa, aa+n);

    memset(memo, -1, sizeof(memo));
    lli ans = solve();
    printf("%lld\n", ans);
  }
  return 0;
}
