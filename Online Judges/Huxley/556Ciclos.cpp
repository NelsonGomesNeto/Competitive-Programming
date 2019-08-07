#include <bits/stdc++.h>
using namespace std;

int hasCycle(vector<int> graph[], int visited[], int u, int parent)
{
  visited[u] = 1;
  for (auto v: graph[u])
  {
    if (visited[v] == 1 && v != parent) return(1);
    if (!visited[v] && hasCycle(graph, visited, v, u)) return(1);
  }
  visited[u] = 2;
  return(0);
}

int main()
{
  int vertices, edges, now = 1;
  while (scanf("%d %d", &vertices, &edges) != EOF)
  {
    vector<int> graph[vertices];
    int u, v;
    for (int i = 0; i < edges; i ++)
    {
      scanf("%d %d", &u, &v);
      graph[u].push_back(v);
      graph[v].push_back(u);
    }

    int visited[vertices]; memset(visited, 0, sizeof(visited));
    printf("%d %d\n", now ++, hasCycle(graph, visited, 0, -1));
  }
  
  return(0);
}