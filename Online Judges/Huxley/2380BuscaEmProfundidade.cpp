#include <bits/stdc++.h>
using namespace std;

const int maxN = 1e5; int n, source;
vector<int> graph[maxN];

bool visited[maxN];
void dfs(int u)
{
  if (visited[u]) return;
  visited[u] = true;
  for (int v: graph[u]) dfs(v);
  printf("%d\n", u);
}

int main()
{
  scanf("%d %d", &n, &source);
  int u, v;
  while (scanf("%d %d", &u, &v) != EOF) graph[u].push_back(v), graph[v].push_back(u);
  for (int i = 0; i < n; i ++) reverse(graph[i].begin(), graph[i].end());
  memset(visited, false, sizeof(visited));
  dfs(source);
  return(0);
}
