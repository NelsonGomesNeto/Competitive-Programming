#include <bits/stdc++.h>
#define lli long long int
using namespace std;

const int maxN = 100; int n, a, b, c;
vector<int> graph[maxN];
int prv[maxN], dist[maxN];
bool visited[maxN];

void bfs(int origin)
{
  memset(visited, false, sizeof(visited));
  queue<pair<int, int>> q; q.push({0, origin});
  dist[origin] = 0, prv[origin] = -1;
  while (!q.empty())
  {
    int u = q.front().second, d = q.front().first; q.pop();
    visited[u] = true, dist[u] = d;
    for (int v: graph[u])
      if (!visited[v])
        prv[v] = u, q.push({d + 1, v});
  }
}

int main()
{
  while (scanf("%d %d %d %d", &n, &a, &b, &c) != EOF)
  {
    a --, b --, c --;
    for (int i = 0; i < n; i ++) graph[i].clear();
    for (int i = 0, u, v; i < n - 1; i ++)
    {
      scanf("%d %d", &u, &v); u --, v --;
      graph[u].push_back(v), graph[v].push_back(u);
    }

    bfs(b);
    vector<int> bcPath;
    for (int u = c; u != b; u = prv[u])
      bcPath.push_back(u);
    bcPath.push_back(b);
    reverse(bcPath.begin(), bcPath.end());

    bfs(a);
    int lca = b, d = 0;
    for (int i = 1; i < bcPath.size(); i ++)
      if (dist[bcPath[i]] < dist[lca])
        lca = bcPath[i], d = i;

    long double p = 1 - (long double) d / (bcPath.size() - 1);
    printf("%.6Lf\n", p);
  }
  return(0);
}