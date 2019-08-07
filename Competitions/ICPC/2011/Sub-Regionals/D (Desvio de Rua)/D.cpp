#include <bits/stdc++.h>
using namespace std;

const int maxN = 1e3; int n, m;
vector<pair<int, int>> graph[maxN], full[maxN], reverseGraph[maxN];
bool visited[maxN];

void dfs(int u = 0, int prv = -1)
{
  if (visited[u]) return;
  visited[u] = true;
  for (auto &e: full[u])
    if (e.first != prv)
      dfs(e.first, u);
}

vector<pair<int, int>> bridges; bool hasBadBridge;
int low[maxN], in[maxN], t;
void tarjanDfs(int u = 0, int prv = -1)
{
  visited[u] = true, in[u] = low[u] = ++ t;
  for (auto &e: full[u])
  {
    int v = e.first;
    if (!visited[v])
    {
      tarjanDfs(v, u);
      low[u] = min(low[u], low[v]);
      if (low[v] > in[u])
      {
        bridges.push_back({u, v});
        if (e.second == 1) hasBadBridge = true;
      }
    }
    else if (v != prv) low[u] = min(low[u], in[v]);
  }
}
void tarjan()
{
  memset(visited, false, sizeof(visited)), bridges.clear(), t = 0, hasBadBridge = false;
  memset(in, 0, sizeof(in)); memset(low, 0, sizeof(low));
  tarjanDfs();
}

vector<vector<int>> stronglyConnectedComponents;
stack<int> visitStack;
void kosarajuDfs(int u, bool bindComponents)
{
  if (visited[u]) return;
  visited[u] = true;
  if (bindComponents)
  {
    stronglyConnectedComponents[stronglyConnectedComponents.size() - 1].push_back(u);
    for (auto &e: reverseGraph[u]) kosarajuDfs(e.first, bindComponents);
  }
  else
  {
    for (auto &e: graph[u]) kosarajuDfs(e.first, bindComponents);
    visitStack.push(u);
  }
}
void kosaraju()
{
  while (!visitStack.empty()) visitStack.pop();
  stronglyConnectedComponents.clear(), memset(visited, false, sizeof(visited));
  for (int i = 0; i < n; i ++) if (!visited[i]) kosarajuDfs(i, false);
  memset(visited, false, sizeof(visited));
  while (!visitStack.empty())
  {
    if (!visited[visitStack.top()])
    {
      stronglyConnectedComponents.push_back(vector<int>());
      kosarajuDfs(visitStack.top(), true);
    }
    visitStack.pop();
  }
}

int main()
{
  while (scanf("%d %d", &n, &m) != EOF && !(n == -1 && m == -1))
  {
    for (int i = 0; i < n; i ++) graph[i].clear(), full[i].clear(), reverseGraph[i].clear();
    for (int i = 0, u, v, c; i < m; i ++)
    {
      scanf("%d %d %d", &u, &v, &c); u --, v --;
      if (!i) continue;
      graph[u].push_back({v, c}), reverseGraph[v].push_back({u, c});
      if (c == 2) graph[v].push_back({u, c}), reverseGraph[u].push_back({v, c});
      full[u].push_back({v, c}), full[v].push_back({u, c});
    }

    memset(visited, false, sizeof(visited));
    dfs();
    char ans = '2';
    for (int i = 0; i < n; i ++) if (!visited[i]) ans = '*';
    if (ans != '*')
    {
      kosaraju();
      if (stronglyConnectedComponents.size() == 1) ans = '-';
      else
      {
        tarjan();
        if (!hasBadBridge) ans = '1';
      }
    }
    printf("%c\n", ans);
  }
  return(0);
}