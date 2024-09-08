#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 2e3; int n, m;
char a[maxN][maxN];

int getPoints(int i, int j, bool taka)
{
  if (!taka)
    return a[i][j] == '+' ? 1 : -1;
  return a[i][j] == '-' ? 1 : -1;
}
int memo[maxN][maxN][2]; bool visited[maxN][maxN][2];
int solve(int i = 0, int j = 0, bool taka = true)
{
  if (i == n - 1 && j == m - 1)
    return getPoints(i, j, taka);

  int &ans = memo[i][j][taka]; bool &vis = visited[i][j][taka];
  if (vis) return ans;
  vis = true;

  if (taka)
  {
    ans = -1e9;
    if (i + 1 < n) ans = max(ans, solve(i + 1, j, !taka));
    if (j + 1 < m) ans = max(ans, solve(i, j + 1, !taka));
    if (!(i == 0 && j == 0)) ans += getPoints(i, j, taka);
  }
  else
  {
    ans = 1e9;
    if (i + 1 < n) ans = min(ans, solve(i + 1, j, !taka));
    if (j + 1 < m) ans = min(ans, solve(i, j + 1, !taka));
    if (!(i == 0 && j == 0)) ans += getPoints(i, j, taka);
  }

  return ans;
}

int main()
{
  while (~scanf("%d %d", &n, &m))
  {
    for (int i = 0; i < n; i++)
      scanf(" %s", a[i]);

    memset(visited, false, sizeof(visited));
    int ans = solve();
    if (ans == 0 || (n == 1 && m == 1))
      printf("Draw\n");
    else if (ans > 0)
      printf("Takahashi\n");
    else
      printf("Aoki\n");
  }
  return 0;
}