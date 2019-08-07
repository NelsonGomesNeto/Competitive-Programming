#include <bits/stdc++.h>
using namespace std;

const int maxN = 1e5; int n, source;
vector<int> graph[maxN];

bool visited[maxN];
void bfs()
{
  queue<int> q; q.push(source);
  while (!q.empty())
  {
    int u = q.front(); q.pop();
    if (visited[u]) continue;
    visited[u] = true; printf("%d\n", u);
    for (int v: graph[u]) q.push(v);
  }
}

int main()
{
  scanf("%d %d", &n, &source);
  int u, v;
  while (scanf("%d %d", &u, &v) != EOF) graph[u].push_back(v), graph[v].push_back(u);
  for (int i = 0; i < n; i ++) reverse(graph[i].begin(), graph[i].end());
  memset(visited, false, sizeof(visited));
  bfs();
  return(0);
}
