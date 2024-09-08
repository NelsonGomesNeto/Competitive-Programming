#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 1e5; int n, m;
int nodes[maxN];
vector<int> graph[maxN];
void addEdge(int u, int v)
{
  graph[u].push_back(v);
  graph[v].push_back(u);
}

int dist[maxN];
pair<int, int> bfs(int source)
{
  memset(dist, -1, sizeof(dist));
  queue<int> q; q.push(source), dist[source] = 0;
  while (!q.empty())
  {
    int u = q.front(); q.pop();
    for (int v: graph[u])
      if (dist[v] == -1)
        dist[v] = dist[u] + 1, q.push(v);
  }
  auto it = max_element(dist, dist+n);
  return make_pair(it - dist, *it);
}
int diameter(int source)
{
  return bfs(bfs(source).first).second;
}

int main()
{
  while (~scanf("%d %d", &n, &m))
  {
    for (int i = 0; i < m; i++)
    {
      int u, v; scanf("%d %d", &u, &v); u--, v--;
      addEdge(u, v);
    }

    bfs(0);
    if (*min_element(dist, dist+n) == -1)
    {
      printf("-1\n");
      continue;
    }

    for (int i = 0; i < n; i++) nodes[i] = i;
    auto rng = default_random_engine {};
    shuffle(nodes, nodes+n, rng);

    int ans = 0;
    for (int i = 0, end = min(1000, n); i < end; i++)
      ans = max(ans, (diameter(nodes[i]) - 1));
    printf("%d\n", ans);
  }
  return 0;
}