#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 2e5, inf = 1e6; int n;
vector<int> tree[maxN];
int prv[maxN], dist[maxN];

int bfs(int source = 0)
{
  for (int i = 0; i < n; i ++) dist[i] = inf, prv[i] = -1;
  queue<int> q; q.push(source), dist[source] = 0;
  while (!q.empty())
  {
    int u = q.front(); q.pop();
    for (int v: tree[u])
      if (dist[v] == inf)
        q.push(v), dist[v] = dist[u] + 1, prv[v] = u;
  }
  return max_element(dist, dist+n) - dist;
}

int main()
{
  while (scanf("%d", &n) != EOF)
  {
    for (int i = 0; i < n - 1; i ++)
    {
      int u, v; scanf("%d %d", &u, &v); u --, v --;
      tree[u].push_back(v), tree[v].push_back(u);
    }

    int o = bfs();
    int mostDistant = bfs(o);
    set<int> inPath;
    for (int u = mostDistant; u != -1; u = prv[u])
      inPath.insert(u);

    int other = -1, otherd = 0;
    for (int u: inPath)
      if (u != o && u != mostDistant)
        other = u;
    for (int i = 0; i < n; i ++)
    {
      int d = 0;
      for (int u = i; !inPath.count(u); u = prv[u], d ++);
      if (d > otherd)
        otherd = d, other = i;
    }
    printf("%d\n%d %d %d\n", (int)inPath.size() - 1 + otherd, o + 1, mostDistant + 1, other + 1);
  }
  return 0;
}