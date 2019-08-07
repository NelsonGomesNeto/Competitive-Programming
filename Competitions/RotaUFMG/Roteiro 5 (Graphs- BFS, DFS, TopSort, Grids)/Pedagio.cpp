#include <bits/stdc++.h>
using namespace std;

void bfs(vector<int> graph[], int start, int visited[], int p)
{
  deque<pair<int, int> > queue;
  queue.push_back({start, p});
  while (!queue.empty())
  {
    int u = queue.front().first, np = queue.front().second; queue.pop_front();
    if (visited[u] || np == -1) continue;
    visited[u] = 1;
    for (auto v: graph[u])
      queue.push_back({v, np - 1});
  }
}

int main()
{
  int c, e, l, p, t = 0;
  while (scanf("%d %d %d %d", &c, &e, &l, &p) && !(!c && !e && !l && !p))
  {
    if (t ++) printf("\n");
    vector<int> graph[c]; int u, v;
    for (int i = 0; i < e; i ++)
    {
      scanf("%d %d", &u, &v); u --; v --;
      graph[u].push_back(v);
      graph[v].push_back(u);
    } l --;

    int visited[c], canVisit = 0; memset(visited, 0, sizeof(visited));
    bfs(graph, l, visited, p);

    printf("Teste %d\n", t);
    for (int i = 0; i < c; i ++)
      if (visited[i] && i != l)
      {
        printf("%s%d", canVisit ? " " : "\0", i + 1);
        canVisit = 1;
      }
    printf("\n");
  }
  return(0);
}