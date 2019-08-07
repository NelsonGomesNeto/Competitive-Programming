#include <bits/stdc++.h>
using namespace std;

const int maxN = 2e5; int n, m, r;
vector<int> graph[maxN];
double probability[maxN]; vector<int> stuck;

bool visited[maxN];
void dfs(int u, double p)
{
  probability[u] += p;
  if (graph[u].empty() && !visited[u]) stuck.push_back(u);
  visited[u] = true;
  for (int v: graph[u]) dfs(v, p * ((double) 1 / graph[u].size()));
}

int stackU[maxN]; double stackP[maxN];
void iterativeDFS()
{
  int sp = 0;
  stackU[sp] = r, stackP[sp ++] = 1;
  while (sp)
  {
    int u = stackU[-- sp]; double p = stackP[sp];
    probability[u] += p;
    if (graph[u].empty() && !visited[u]) stuck.push_back(u);
    visited[u] = true;
    for (int v: graph[u]) stackU[sp] = v, stackP[sp ++] = p * ((double) 1 / graph[u].size());
  }
}

int indegree[maxN];
void topologicalSortBFS()
{
  queue<int> q;
  for (int i = 0; i < n; i ++) if (!indegree[i]) q.push(i);
  while (!q.empty())
  {
    int u = q.front(); q.pop();
    if (graph[u].empty()) stuck.push_back(u);
    for (int v: graph[u])
    {
      probability[v] += probability[u] * ((double) 1 / graph[u].size());
      if (-- indegree[v] == 0) q.push(v);
    }
  }
}

int main()
{
  scanf("%d %d %d", &n, &m, &r); r --;
  for (int i = 0, u, v; i < m; i ++)
  {
    scanf("%d %d", &u, &v); u --, v --;
    graph[u].push_back(v), indegree[v] ++;
  }

  // dfs(r, 1);
  // iterativeDFS();
  probability[r] = 1;
  topologicalSortBFS();
  vector<int> best; double p = -1;
  for (int s: stuck)
    if (abs(probability[s] - p) <= 1e-9) best.push_back(s);
    else if (probability[s] - p > 1e-9)
    {
      best.clear();
      p = probability[s], best.push_back(s);
    }
  sort(best.begin(), best.end());

  for (int i = 0; i < best.size(); i ++)
    printf("%d%c", best[i] + 1, i < best.size() - 1 ? ' ' : '\n');
  return(0);
}