#include <bits/stdc++.h>
#define lli long long int
using namespace std;

const int maxN = 1000; int n, c, t1, t2;
int holes[maxN];

int memo[maxN][maxN][2];
int solve(int i = 0, int coverage = 0, int pos = 0, int type = 0)
{
  if (i == n) return(0);
  if (memo[i][pos][type] == -1)
  {
    int ans = solve(i + 1, holes[i] + t1, i, 0) + t1;
    ans = min(ans, solve(i + 1, holes[i] + t2, i, 1) + t2);
    if (coverage >= holes[i]) ans = min(ans, solve(i + 1, coverage, pos, type));
    memo[i][pos][type] = ans;
  }
  return(memo[i][pos][type]);
}

int main()
{
  while (scanf("%d %d %d %d", &n, &c, &t1, &t2) != EOF)
  {
    for (int i = 0; i < n; i ++) scanf("%d", &holes[i]);

    memset(memo, -1, sizeof(memo));
    int ans = solve();
    printf("%d\n", ans);
  }
  return(0);
}