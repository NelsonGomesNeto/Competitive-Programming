#include <bits/stdc++.h>
using namespace std;

const int maxVertices = 100;
vector<int> graph[maxVertices], revGraph[maxVertices];
map<string, int> cityToInt;
string intToCity[maxVertices];

int prv[maxVertices], allowedEdge[maxVertices][maxVertices]; bool visited[maxVertices];
int blockedFrom, blockedTo;
void dfs(vector<int> g[], int u, bool avoid)
{
  visited[u] = true;
  for (int v: g[u])
  {
    if (visited[v]) continue;
    if (avoid && !(u == blockedFrom && v == blockedTo))
      dfs(g, v, avoid);
    else if (!avoid)
      dfs(g, v, avoid), allowedEdge[v][u] --, prv[v] = u;
  }
}

int main()
{
  int n, m, r = 0;
  while (scanf("%d %d", &n, &m) && (n || m))
  {
    if (r ++) printf("\n");
    cityToInt.clear(); for (int i = 0; i < n; i ++) graph[i].clear(), revGraph[i].clear();
    for (int i = 0; i < n; i ++)
    {
      string city; cin >> city;
      cityToInt[city] = i, intToCity[i] = city;
    }

    memset(allowedEdge, 0, sizeof(allowedEdge));
    vector<pair<int, int>> inputEdges;
    for (int i = 0; i < m; i ++)
    {
      string u, v; cin >> u >> v;
      allowedEdge[cityToInt[u]][cityToInt[v]] ++;
      inputEdges.push_back({cityToInt[u], cityToInt[v]});
      graph[cityToInt[v]].push_back(cityToInt[u]);
      revGraph[cityToInt[u]].push_back(cityToInt[v]);
    }

    memset(visited, false, sizeof(visited));
    int cl = 0; bool criticalLinks[n][n]; memset(criticalLinks, false, sizeof(criticalLinks));
    dfs(graph, 0, false);
    for (int i = 1; i < n; i ++)
    {
      memset(visited, false, sizeof(visited));
      blockedFrom = i, blockedTo = prv[i];
      if (allowedEdge[blockedFrom][blockedTo] == 0) dfs(revGraph, i, true);
      else continue;
      if (!visited[0]) criticalLinks[i][prv[i]] = true, cl ++;
    }

    if (!cl) printf("Nenhuma\n");
    else
      for (auto e: inputEdges)
        if (criticalLinks[e.first][e.second])
          cout << intToCity[e.first] << " " << intToCity[e.second] << endl;
  }
  return(0);
}