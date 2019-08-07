#include <bits/stdc++.h>
#define lli long long int
using namespace std;
int n, m;

lli bfs(vector<int> graph[], int source, int bananas[])
{
  deque<int> q; q.push_back(source);
  lli total = 0;
  while (!q.empty())
  {
    int u = q.front(); q.pop_front();
    if (bananas[u] == -1) continue;
    total += bananas[u]; bananas[u] = -1;
    for (auto v: graph[u]) q.push_back(v);
  }
  return(total);
}

int main()
{
  int t; scanf("%d", &t);
  while (t --)
  {
    scanf("%d %d", &n, &m);
    vector<int> graph[n];
    for (int i = 0; i < m; i ++)
    {
      int u, v; scanf("%d %d", &u, &v); u --; v --;
      graph[u].push_back(v);
      graph[v].push_back(u);
    }
    int bananas[n]; for (int i = 0; i < n; i ++) scanf("%d", &bananas[i]);
    lli best = 0;
    for (int i = 0; i < n; i ++) best = max(best, bfs(graph, i, bananas));
    printf("%lld\n", best);
  }
  return(0);
}