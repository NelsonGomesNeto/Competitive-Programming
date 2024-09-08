#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 100; int n, m;
char mat[maxN][maxN + 1];

int memo[maxN][maxN];
int solve(int i = 0, int j = 0)
{
  if (i >= n || j >= m) return 0;
  if (mat[i][j] == '#') return 0;

  int &ans = memo[i][j];
  if (ans != -1) return ans;

  return ans = 1 + max(solve(i + 1, j), solve(i, j + 1));
}

int main()
{
  while (~scanf(" %d %d", &n, &m))
  {
    for (int i = 0; i < n; i++) scanf(" %s", mat[i]);

    memset(memo, -1, sizeof(memo));
    int ans = solve();
    printf("%d\n", ans);
  }
  return 0;
}