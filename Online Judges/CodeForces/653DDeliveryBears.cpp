#include <bits/stdc++.h>
#define lli long long int
using namespace std;

/* Explanation:
Do a binary search to find to total
For each evaulation: you must rebuild the graph changing the capacity of each edge
The capacity will be a multiple of the input, but will change accordingly to the desired total
Since a bear will carry total / x, and we can't divide a bear: we divide the capacity by total / x
This will round a bear to 1 (integer), then we run a simple flow algorithm
*/

const int maxVertices = 50;
int n, m, x;
int source = 0, target, vertices; lli inf = 1e18;
int level[maxVertices], ptr[maxVertices], edges[500][3];
queue<int> q;
struct Edge { int to, back; lli capacity, flow; };
vector<Edge> graph[maxVertices];
void addEdge(int u, int v, lli f)
{
  graph[u].push_back({v, (int) graph[v].size(), f, f});
  graph[v].push_back({u, (int) graph[u].size() - 1, 0, 0});
}
bool bfs()
{
  memset(level, -1, sizeof(level)); level[source] = 0; q.push(source);
  while (!q.empty())
  {
    int u = q.front(); q.pop();
    for (Edge &e: graph[u])
      if (e.flow && level[e.to] == -1)
        q.push(e.to), level[e.to] = level[u] + 1;
  }
  return(level[target] != -1);
}
lli dfs(int u, lli flow)
{
  if (u == target || flow == 0) return(flow);
  for (int &p = ptr[u]; p < graph[u].size(); p ++)
  {
    Edge &e = graph[u][p];
    if (e.flow && level[u] == level[e.to] - 1)
    {
      lli delivered = dfs(e.to, min(flow, e.flow));
      e.flow -= delivered;
      graph[e.to][e.back].flow += delivered;
      if (delivered) return(delivered);
    }
  }
  return(0);
}
lli maxFlow()
{
  lli maxFlow = 0, flow;
  while (bfs())
  {
    memset(ptr, 0, sizeof(ptr));
    while (flow = dfs(source, inf)) maxFlow += flow;
  }
  return(maxFlow);
}
lli eval(double v)
{
  for (int i = 0; i < vertices; i ++) graph[i].clear();
  for (int i = 0; i < m; i ++)
  {
    addEdge(edges[i][0], edges[i][1], floor(edges[i][2] / v));
    //addEdge(edges[i][0], edges[i][1], edges[i][2]);
    // printf("%d -> %d (%lld)\n", edges[i][0], edges[i][1], (lli) floor(edges[i][2] / v));
  }
  return(maxFlow());
}

double binarySearch(double lo, double hi)
{
  while (lo + 1e-8 < hi)
  {
    double mid = (lo + hi) / 2.0; lli evaluated = eval(mid / x);
    // printf("eval(%lf) = %lld - %lf %f\n", mid, evaluated, lo, hi);
    if (evaluated < x) hi = mid;
    else lo = mid;
  }
  return((lo + hi) / 2.0);
}

int main()
{
  scanf("%d %d %d", &n, &m, &x); target = n - 1; vertices = n;
  for (int i = 0; i < m; i ++)
  {
    int u, v, c; scanf("%d %d %d", &u, &v, &c); u --, v --;
    edges[i][0] = u, edges[i][1] = v, edges[i][2] = c;
  }

  printf("%.6lf\n", binarySearch(0, 1e9));

  return(0);
}