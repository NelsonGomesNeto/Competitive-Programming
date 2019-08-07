#include <bits/stdc++.h>
#define lli long long int
using namespace std;

const int maxN = 1e5; int n, m;
const lli inf  = 1e18, mod = 1e9 + 7;
lli cost[maxN];
vector<int> graph[maxN], reverseGraph[maxN];

bool visited[maxN]; stack<int> visitStack;
vector<vector<int>> stronglyConnectedComponents;
void dfs(int u, bool bindComponents = false)
{
  if (visited[u]) return;
  visited[u] = true;
  if (bindComponents)
  {
    stronglyConnectedComponents[stronglyConnectedComponents.size() - 1].push_back(u);
    for (int v: graph[u]) dfs(v, bindComponents);
  }
  else
  {
    for (int v: reverseGraph[u]) dfs(v, bindComponents);
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
  scanf("%d", &n); for (int i = 0; i < n; i ++) scanf("%lld", &cost[i]);
  scanf("%d", &m); for (int i = 0, u, v; i < m; i ++) { scanf("%d %d", &u, &v); u --, v --; graph[u].push_back(v), reverseGraph[v].push_back(u); }
  kosaraju();

  lli cheapestInComponent[stronglyConnectedComponents.size()], totalCost = 0, combinations = 1;
  int costFrequency[stronglyConnectedComponents.size()];
  memset(costFrequency, 0, sizeof(costFrequency));
  for (int i = 0; i < stronglyConnectedComponents.size(); i ++) cheapestInComponent[i] = inf;
  for (int i = 0; i < stronglyConnectedComponents.size(); i ++)
    for (int j: stronglyConnectedComponents[i])
      cheapestInComponent[i] = min(cheapestInComponent[i], cost[j]);
  for (int i = 0; i < stronglyConnectedComponents.size(); i ++)
  {
    for (int j: stronglyConnectedComponents[i])
      costFrequency[i] += cost[j] == cheapestInComponent[i];
    totalCost += cheapestInComponent[i], combinations = (combinations * costFrequency[i]) % mod;
  }

  printf("%lld %lld\n", totalCost, combinations);

  return(0);
}