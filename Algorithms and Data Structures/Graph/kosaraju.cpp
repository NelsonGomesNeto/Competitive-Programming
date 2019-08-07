#include <bits/stdc++.h>
using namespace std;

const int maxN = 1e5; int n, m;
vector<int> graph[maxN], reverseGraph[maxN];

vector<vector<int>> stronglyConnectedComponents;
stack<int> visitStack;
bool visited[maxN];
void dfs(int u, bool bindComponents = false)
{
  if (visited[u]) return;
  visited[u] = true;
  if (bindComponents)
  {
    stronglyConnectedComponents[stronglyConnectedComponents.size() - 1].push_back(u);
    for (int v: reverseGraph[u]) dfs(v, bindComponents);
  }
  else
  {
    for (int v: graph[u]) dfs(v, bindComponents);
    visitStack.push(u);
  }
}
void kosaraju()
{
  for (int i = 0; i < n; i ++) if (!visited[i]) dfs(i);
  memset(visited, false, sizeof(visited));
  while (!visitStack.empty())
  {
    if (!visited[visitStack.top()])
    {
      stronglyConnectedComponents.push_back(vector<int>());
      dfs(visitStack.top(), true);
    }
    visitStack.pop();
  }
}

int main()
{
  scanf("%d %d", &n, &m);
  for (int i = 0, u, v; i < m; i ++)
  {
    scanf("%d %d", &u, &v);
    graph[u].push_back(v), reverseGraph[v].push_back(u);
  }
  kosaraju();

  printf("%d strongly connected components\n", (int) stronglyConnectedComponents.size());
  for (int i = 0; i < stronglyConnectedComponents.size(); i ++)
  {
    printf("%d: ", i);
    for (int j = 0; j < stronglyConnectedComponents[i].size(); j ++)
      printf("%d%c", stronglyConnectedComponents[i][j], j < stronglyConnectedComponents[i].size() - 1 ? ' ' : '\n');
  }

  return(0);
} 