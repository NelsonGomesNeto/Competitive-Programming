#include <bits/stdc++.h>
using namespace std;
const int maxVertices = 1 + 1000 + 1000 + 1;
int p, r, c, vertices, source, target, canFlow = 0, minFlow = 0, inf = 1<<20;
int flowP[1001], flowR[1001];
int matrixGraph[maxVertices][maxVertices], level[maxVertices];
vector<int> graph[maxVertices];
int edges[20000][3]; // {u, v, t}

int bfs()
{
  memset(level, -1, sizeof(level)); level[source] = 0;
  deque<int> queue; queue.push_back(source);
  while (!queue.empty())
  {
    int u = queue.front(); queue.pop_front();
    for (auto v: graph[u])
      if (level[v] < 0 && matrixGraph[u][v] > 0)
        level[v] = level[u] + 1, queue.push_back(v);
  }
  return(level[target] > 0);
}

int dfs(int u, int flow)
{
  if (u == target) return(flow);
  int actualFlow = 0;
  for (auto v: graph[u])
    if (level[u] == level[v] - 1 && matrixGraph[u][v] > 0)
    {
      int pathFlow = dfs(v, min(flow, matrixGraph[u][v]));
      flow -= pathFlow;
      matrixGraph[u][v] -= pathFlow;
      matrixGraph[v][u] += pathFlow;
      actualFlow += pathFlow;
    }
  return(actualFlow);
}

int dinic()
{
  int maxFlow = 0;
  while (bfs()) maxFlow += dfs(source, inf);
  return(maxFlow);
}

int eval(int tim)
{
  for (int i = 1; i <= p; i ++)
  {
    matrixGraph[r + i][target] = flowP[i];
    matrixGraph[target][r + i] = 0;
  }
  for (int i = 1; i <= r; i ++)
  {
    matrixGraph[source][i] = flowR[i];
    matrixGraph[i][source] = 0;
  }
  for (int i = 0; i < c; i ++)
  {
    matrixGraph[edges[i][1]][r + edges[i][0]] = inf * (edges[i][2] <= tim);
    matrixGraph[r + edges[i][0]][edges[i][1]] = 0;
  }
  return(dinic());
}

int binSearch(int lo, int hi)
{
  while (lo < hi)
  {
    int mid = (lo + hi) / 2;
    if (eval(mid) >= minFlow) hi = mid;
    else lo = mid + 1;
  }
  return(lo);
  // if (lo >= hi) return(lo);
  // int mid = (lo + hi) / 2;
  // if (eval(mid) >= minFlow) return(binSearch(lo, mid));
  // return(binSearch(mid + 1, hi));
}

void addEdge(int u, int v, int f)
{
  graph[u].push_back(v);
  matrixGraph[u][v] = f;
  graph[v].push_back(u);
  matrixGraph[v][u] = 0;
}

int main()
{
  scanf("%d %d %d", &p, &r, &c); vertices = 1 + p + r + 1;
  source = 0, target = vertices - 1;

  int f;
  for (int pi = 1; pi <= p; pi ++)
  {
    scanf("%d", &f); minFlow += f; flowP[pi] = f;
    addEdge(r + pi, target, f);
  }
  for (int ri = 1; ri <= r; ri ++)
  {
    scanf("%d", &f); canFlow += f; flowR[ri] = f;
    addEdge(source, ri, f);
  }

  int mt = 0;
  for (int i = 0; i < c; i ++)
  {
    scanf("%d %d %d", &edges[i][0], &edges[i][1], &edges[i][2]);
    addEdge(edges[i][1], r + edges[i][0], inf);
    mt = max(mt, edges[i][2]);
  }

  int maxTime = canFlow >= minFlow ? binSearch(0, mt) : -1;
  if (eval(maxTime) < minFlow) printf("-1\n");
  else printf("%d\n", maxTime);
  return(0);
}