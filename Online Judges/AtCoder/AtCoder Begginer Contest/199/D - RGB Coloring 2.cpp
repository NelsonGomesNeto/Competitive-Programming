#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 20; int n, m;
vector<int> graph[maxN];
vector<int> above[maxN];

lli pot3[maxN + 1];

int colors[maxN];
lli solve(int u = 0)
{
  if (u == n) return 1;

  lli ans = 0;
  if (graph[u].empty() && above[u].empty())
    ans += 3*solve(u + 1);
  else
    for (int c = 0; c < 3; c++)
    {
      bool can = true;
      for (int v: graph[u])
        if (colors[v] == c)
        {
          can = false;
          break;
        }
      if (can)
      {
        colors[u] = c;
        ans += solve(u + 1);
      }
    }
  return ans;
}

int main()
{
  pot3[0] = 1;
  for (int i = 1; i <= maxN; i++)
    pot3[i] = pot3[i - 1] * 3;

  while (~scanf("%d %d", &n, &m))
  {
    for (int i = 0; i < n; i++)
      graph[i].clear(), above[i].clear();

    for (int i = 0; i < m; i++)
    {
      int u, v; scanf("%d %d", &u, &v); u--, v--;
      if (u < v) swap(u, v);
      graph[u].push_back(v);
      above[v].push_back(u);
    }

    lli ans = solve();
    printf("%lld\n", ans);
  }
  return 0;
}