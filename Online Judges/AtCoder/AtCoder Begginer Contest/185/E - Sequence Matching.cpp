#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 1e3; int n, m;
lli a[maxN], b[maxN];

const int inf = 10*maxN;
int memo[maxN + 1][maxN + 1];
int solve(int i = 0, int j = 0)
{
  if (i == n && j == m) return 0;
  // if (i == n || j == m) return inf;
  // if (j == m) return inf;
  int &ans = memo[i][j];
  if (ans != -1) return ans;

  ans = inf;
  if (i < n && j < m)
    ans = min(ans, solve(i + 1, j + 1) + (a[i] != b[j]));
  if (j < m)
    ans = min(ans, solve(i, j + 1) + 1);
  if (i < n)
    ans = min(ans, solve(i + 1, j) + 1);

  return ans;
}

int main()
{
  while (~scanf("%d %d", &n, &m))
  {
    for (int i = 0; i < n; i++)
      scanf("%lld", &a[i]);
    for (int i = 0; i < m; i++)
      scanf("%lld", &b[i]);

    memset(memo, -1, sizeof(memo));
    int ans = solve();
    printf("%d\n", ans);
  }
  return 0;
}