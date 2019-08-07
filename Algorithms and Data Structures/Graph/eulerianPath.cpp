#include <bits/stdc++.h>
using namespace std;
const int maxN = 1e5; int n, m;

/* Eulerian checks:
  The graph MUST be connected for both checks
  0 odd degree -> Eulerian Cycle
  2 odd degree -> Eulerian Path
    Starts and ends in the vertices that have odd degree
*/

struct Edge { int to, back; bool visited; };
vector<Edge> graph[maxN];
void addEdge(int u, int v)
{
  graph[u].push_back({v, (int) graph[v].size() + (u == v), false});
  graph[v].push_back({u, (int) graph[u].size() - 1, false});
}

vector<int> path;
int ptr[maxN];
void eulerianPath(int u)
{
  for (int &p = ptr[u]; p < graph[u].size(); p ++)
  {
    auto &e = graph[u][p];
    if (!e.visited)
    {
      e.visited = true, graph[e.to][e.back].visited = true;
      eulerianPath(e.to);
    }
  }
  path.push_back(u);
}

int main()
{
  scanf("%d %d", &n, &m);
  for (int i = 0, u, v;  i < m; i ++)
  {
    scanf("%d %d", &u, &v);
    addEdge(u, v);
  }
  int odd = 0, first = 0;
  for (int i = 0; i < n; i ++)
    if (graph[i].size() & 1)
      odd ++, first = i;
  eulerianPath(first);

  reverse(path.begin(), path.end());
  for (int i: path) printf("%d -> ", i);
  printf("¬\n");

  return(0);
}