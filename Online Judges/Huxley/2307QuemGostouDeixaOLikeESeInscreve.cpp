#include <bits/stdc++.h>
using namespace std;

const int maxVertices = 3e2 + 1;
vector<int> graph[maxVertices];

int dfs(int u, int depth)
{
  if (depth == -1) return(0);
  int total = 1;
  for (int v: graph[u]) total += dfs(v, depth - 1);
  return(total);
}

int main()
{
  int x, y, n; scanf("%d %d %d", &x, &y, &n);
  for (int v = 1, u; v <= n; v ++)
  {
    scanf("%d", &u);
    graph[u].push_back(v);
  }
  int subscribed = dfs(0, y);
  printf("%c\n", subscribed > x ? 'S' : 'N');
  return(0);
}
