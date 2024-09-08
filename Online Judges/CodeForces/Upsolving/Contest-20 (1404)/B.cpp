#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 1e5; int n, a, b, da, db;
const int inf = 1e6;
vector<int> tree[maxN];

int dist[2][maxN];
bool visited[maxN];
void bfs(int k, int u, int du)
{
  memset(visited, false, sizeof(visited));
  for (int i = 0; i < n; i++)
    dist[k][i] = inf;

  dist[k][u] = 0;
  queue<pair<int, int>> q; q.push({u, 0});
  while (!q.empty())
  {
    int u = q.front().first, d = q.front().second; q.pop();
    dist[k][u] = d;
    // if (d == du) continue;
    if (visited[u]) continue;
    visited[u] = true;
    for (int v: tree[u])
      q.push({v, d + 1});
  }
}

int main()
{
  int t;
  while (scanf("%d", &t) != EOF)
  {
    for (int tt = 1; tt <= t; tt++)
    {
      scanf("%d %d %d %d %d", &n, &a, &b, &da, &db); a--, b--;
      for (int i = 0; i < n; i++) tree[i].clear();
      for (int i = 1; i < n; i++)
      {
        int u, v; scanf("%d %d", &u, &v); u--, v--;
        tree[u].push_back(v), tree[v].push_back(u);
      }

      bool alice = false;
      for (int k = 0; k < 10; k++)
      {
        bfs(1, b, db);
        int best = a, bestDist = inf;
        for (int i = 0; i < n; i++)
          if (dist[1][i] < bestDist && dist[1][a] - dist[1][i] < da)
            bestDist = dist[1][i], best = i;
        a = best;
        if (b == a)
          alice = true;

        bfs(0, b, db);
        bfs(1, a, da);
        best = b, bestDist = 0;
        for (int i = 0; i < n; i++)
          if (dist[0][i] <= db && dist[1][i] > bestDist)
            bestDist = dist[1][i], best = i;
        b = best;
        
        printf("\t%d %d\n", a + 1, b + 1);
        if (b == a)
          alice = true;
      }

      printf("%s\n", alice ? "Alice" : "Bob");
    }
  }
  return 0;
}
