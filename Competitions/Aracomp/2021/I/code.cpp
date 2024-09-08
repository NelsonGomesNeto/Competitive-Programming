#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 1e3; int n, r;
const int inf = 1e6;
struct Promo
{
  int x, z, y;
  void read()
  {
    char t;
    scanf("%d %c %d", &x, &t, &y);
    z = t == 'B' ? 1 : t == 'C' ? 2 : 4;
  }
};
Promo promos[maxN];

int memo[maxN][maxN + 1][8];
int solve(int i = 0, int mask = 0, int b = r)
{
  if (mask == 7 || b < 0) return -inf;
  if (i == n) return 0;
  int &ans = memo[i][b][mask];
  if (ans != -1) return ans;

  ans = max({
    solve(i + 1, mask, b),
    solve(i + 1, mask | promos[i].z, b - promos[i].y) + promos[i].x
  });

  return ans;
}

int main()
{
  while (~scanf("%d %d", &n, &r))
  {
    for (int i = 0; i < n; i++)
      promos[i].read();

    memset(memo, -1, sizeof(memo));
    int ans = solve();
    printf("%d\n", ans);
  }
  return 0;
}