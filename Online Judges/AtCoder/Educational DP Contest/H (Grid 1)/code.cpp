#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 1e3; int n, m;
const lli mod = 1e9 + 7;
char mat[maxN][maxN + 1];

int di[2] = {0, 1}, dj[2] = {1, 0};
lli memo[maxN][maxN];
lli solve(int i = 0, int j = 0)
{
  if (i >= n || j >= m || mat[i][j] == '#') return 0;
  if (i == n - 1 && j == m - 1) return 1;
  lli &ans = memo[i][j];
  if (ans != -1) return ans;

  ans = 0;
  for (int k = 0; k < 2; k++)
    ans = (ans + solve(i + di[k], j + dj[k])) % mod;
  return ans;
}

int main()
{
  while (scanf("%d %d", &n, &m) != EOF)
  {
    for (int i = 0; i < n; i++)
      scanf(" %s", mat[i]);

    memset(memo, -1, sizeof(memo));
    lli ans = solve();
    printf("%lld\n", ans);
  }
  return 0;
}