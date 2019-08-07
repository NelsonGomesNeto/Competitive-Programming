#include <bits/stdc++.h>
using namespace std;

int floodFill(int vertices, vector<int> graph[], int visited[], int maxCats, int i, int now, int cats[])
{
  if (visited[i]) return(0);
  visited[i] = 1;
  
  if (cats[i])
    now += cats[i];
  else
    now = 0;
  if (now > maxCats) return(0);
  if (graph[i].size() == 1 && i != 0) return(1);

  int total = 0;
  for (auto u : graph[i])
  {
    total += floodFill(vertices, graph, visited, maxCats, u, now, cats);
  }
  return(total);
}

int main()
{
  int vertices, maxCats; scanf("%d %d", &vertices, &maxCats);
  int cats[vertices], i;
  for (i = 0; i < vertices; i ++) scanf("%d", &cats[i]);

  vector<int> graph[vertices]; int u, v;
  for (i = 0; i < vertices - 1; i ++)
  {
    scanf("%d %d", &u, &v); u --; v --;
    graph[u].push_back(v);
    graph[v].push_back(u);
  }

  int visited[vertices]; memset(visited, 0, sizeof(visited));
  int answer = floodFill(vertices, graph, visited, maxCats, 0, 0, cats);

  printf("%d\n", answer);

  return(0);
}