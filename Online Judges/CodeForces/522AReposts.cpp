#include <bits/stdc++.h>
using namespace std;

int dfs(map<string, vector<string> > graph, map<string, int> visited, string u, int level)
{
  if (visited[u]) return(level);
  if (!graph[u].size()) return(level);
  visited[u] = 1;
  int best = 1;
  for (auto v: graph[u])
    best = max(best, dfs(graph, visited, v, level + 1));
  return(best);
}

void lowerCase(string& s)
{
  for (int i = 0; s[i]; i ++)
    s[i] = tolower(s[i]);
}

int main()
{
  int connections; scanf("%d\n", &connections);
  map<string, vector<string> > graph;
  map<string, int> visited;

  string u, v, t;
  for (int i = 0; i < connections; i ++)
  {
    cin >> u >> t >> v;
    getchar();
    lowerCase(u); lowerCase(v);
    graph[v].push_back(u);
    visited[u] = 0; visited[v] = 0;
  }

  int shares = dfs(graph, visited, "polycarp", 1);

  printf("%d\n", shares);

  return(0);
}