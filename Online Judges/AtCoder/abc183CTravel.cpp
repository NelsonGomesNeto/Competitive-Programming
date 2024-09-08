#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 8; int n; lli k;
lli t[maxN][maxN];
int allVisited;

lli dfs(int u = 0, int visited = 0, lli cost = 0)
{
  if (u == 0 && visited == allVisited) return cost == k;
  if (visited & (1 << u)) return 0;
  visited |= 1 << u;

  lli ans = 0;
  for (int v = 0; v < n; v++)
    ans += dfs(v, visited, cost + t[u][v]);
  return ans;
}

int main()
{
  while (scanf("%d %lld", &n, &k) != EOF)
  {
    allVisited = (1 << n) - 1;
    for (int i = 0; i < n; i++)
      for (int j = 0; j < n; j++)
        scanf("%lld", &t[i][j]);

    lli ans = dfs();
    printf("%lld\n", ans);
  }
  return 0;
}