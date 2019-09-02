#include <bits/stdc++.h>
#define lli long long int
using namespace std;

const int maxN = 1e3; int n;
const lli inf = 1e9;
int a[maxN];

lli memo[maxN][maxN][2];
lli solve(int lo = 0, int hi = n - 1, bool turn = true)
{
  if (lo > hi) return 0;
  if (memo[lo][hi][turn] == -1)
  {
    lli ans;
    if (turn)
      ans = max(solve(lo + 1, hi, !turn) + a[lo], solve(lo, hi - 1, !turn) + a[hi]);
    else
      ans = a[lo] >= a[hi] ? solve(lo + 1, hi, !turn) - a[lo] : solve(lo, hi - 1, !turn) - a[hi];
    memo[lo][hi][turn] = ans;
  }
  return memo[lo][hi][turn];
}

int main()
{
  int t = 1;
  while (scanf("%d", &n) && n)
  {
    // printf("%d\n", n); fflush(stdout);
    for (int i = 0; i < n; i ++)
      scanf("%d", &a[i]);

    for (int i = 0; i < n; i ++) for (int j = 0; j < n; j ++) memo[i][j][0] = memo[i][j][1] = -1;
    // memset(memo, -1, sizeof(memo));
    lli ans = solve();
    printf("In game %d, the greedy strategy might lose by as many as %lld points.\n", t ++, ans);
  }
  return(0);
}