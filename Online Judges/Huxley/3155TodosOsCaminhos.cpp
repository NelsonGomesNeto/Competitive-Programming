#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 1e6; int n, m, source, target;
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

int nodeComponent[maxN];
vector<int> smallGraph[maxN];

bool isIn[maxN];
vector<int> nodesSet;
set<pair<int, int>> componentsEdges, edgesSet;

bool dfs(int u = nodeComponent[source], int prv = -1)
{
  if (u == nodeComponent[target])
  {
    isIn[u] = true;
    return true;
  }

  bool has = false;
  for (int v: smallGraph[u])
    if (v != prv && dfs(v, u))
    {
      has = true;
      componentsEdges.insert({u, v});
    }

  if (has)
    isIn[u] = true;
  return has;
}

void addEdgesFromComponent(int i)
{
  queue<int> q; q.push(stronglyConnectedComponents[i][0]);
  while (!q.empty())
  {
    int u = q.front(); q.pop();
    if (visited[u]) continue;
    visited[u] = true;
    for (int v: graph[u])
      if (nodeComponent[u] == nodeComponent[v])
      {
        q.push(v);
        edgesSet.insert({u, v});
      }
  }
}

int main()
{
  while (scanf("%d %d", &n, &m) != EOF)
  {
    for (int i = 0; i < n; i++)
      graph[i].clear(), reverseGraph[i].clear(), smallGraph[i].clear();
    stronglyConnectedComponents.clear();
    nodesSet.clear(), edgesSet.clear(), componentsEdges.clear();

    for (int i = 0; i < m; i++)
    {
      int u, v; scanf("%d %d", &u, &v);
      graph[u].push_back(v), reverseGraph[v].push_back(u);
    }
    scanf("%d %d", &source, &target);

    kosaraju();
    for (int i = 0; i < stronglyConnectedComponents.size(); i++)
      for (int u: stronglyConnectedComponents[i])
        nodeComponent[u] = i;

    for (int u = 0; u < n; u++)
      for (int v: graph[u])
        if (nodeComponent[u] != nodeComponent[v])
          smallGraph[nodeComponent[u]].push_back(nodeComponent[v]);

    memset(isIn, false, sizeof(isIn));
    dfs();

    memset(visited, false, sizeof(visited));
    for (int i = 0; i < stronglyConnectedComponents.size(); i++)
      if (isIn[i])
      {
        for (int u: stronglyConnectedComponents[i])
          nodesSet.push_back(u);
        addEdgesFromComponent(i);
      }
    sort(nodesSet.begin(), nodesSet.end());

    for (int u = 0; u < n; u++)
      for (int v: graph[u])
        if (componentsEdges.count({nodeComponent[u], nodeComponent[v]}))
          edgesSet.insert({u, v});

    printf("Nodes set:\n");
    for (int u: nodesSet) printf("%d\n", u);
    printf("Edges set:\n");
    for (pair<int, int> uv: edgesSet) printf("(%d, %d)\n", uv.first, uv.second);
  }
  return 0;
}