#include <bits/stdc++.h>
#define RETRIEVE if(1)
using namespace std;
// left, down, right, up
int dy[4] = {0, 1, 0, -1}, dx[4] = {-1, 0, 1, 0};
// line (1 (horizontal) : 2 (vertical)) flow 2
// corner (3 (left, down), 4 (right, down), 5 (right, up), 6 (left, up)) flow 2
// square (7 (left), 8 (down), 9 (right), 10 (up)) flow 2
// dot (11 (left), 12 (down), 13 (right), 14 (up)) flow 1
map<pair<int, int>, int> mapDirToCorner = {{{0, 1}, 3}, {{0, 3}, 6}, {{1, 2}, 4}, {{2, 3}, 5}};

const int maxVertices = 4*20*20 + 2, inf = 1<<20;
/* Explanation:
  We're gonna map every cell to their neighboars
    dots are mapped from 0 to n*m - 1 and will have capacity 1
    not dots will need three vertices: (and will have capacity 2)
      (1*n*m to 2*n*m - 1) horizontal (1)
      (2*n*m to 3*n*m - 1) vertical (2)
      (3*n*m to 4*n*m - 1) unification (3) of vertical and horizontal (to ensure only two of flow will pass to that cell)
      accordingly to what was choosed, we can map it to a piece and orientation
      example:
        horizontal with flow 2
          if comes from two different sides: horizontal line
          if comes from the same side: "square" to that side
        horizontal and vertical with flow 1: corner according to the sides the flows comes
  First layer: even pieces
  Second layer: odd pieces
  source (4*20*20) -> even pieces -> odd pieces -> target (4*20*20 + 1)
  match will be: n*m - (dots / 2)
*/
int source = 4*20*20, target = 4*20*20 + 1, vertices = maxVertices;
int level[maxVertices], ptr[maxVertices];
struct Edge { int to, back, flow, capacity; };
vector<Edge> graph[maxVertices];
deque<int> q;
void addEdge(int u, int v, int f)
{
  graph[u].push_back({v, (int) graph[v].size(), f, f});
  graph[v].push_back({u, (int) graph[u].size() - 1, 0, 0});
}

bool bfs()
{
  memset(level, -1, sizeof(level));
  level[source] = 0; q.push_back(source);
  while (!q.empty())
  {
    int u = q.front(); q.pop_front();
    for (Edge &e: graph[u])
      if (e.flow && level[e.to] == -1)
        q.push_back(e.to), level[e.to] = level[u] + 1;
  }
  return(level[target] != -1);
}

int dfs(int u, int flow)
{
  if (u == target || !flow) return(flow);
  for (int &p = ptr[u]; p < graph[u].size(); p ++)
  {
    Edge &e = graph[u][p];
    if (e.flow && level[e.to] == level[u] + 1)
    {
      int delivered = dfs(e.to, min(flow, e.flow));
      e.flow -= delivered;
      graph[e.to][e.back].flow += delivered;
      if (delivered) return(delivered);
    }
  }
  return(0);
}

int dinic()
{
  int maxFlow = 0, flow;
  while (bfs())
  {
    memset(ptr, 0, sizeof(ptr));
    while (flow = dfs(source, inf)) maxFlow += flow;
  }
  return(maxFlow);
}

int main()
{
  int n, m; scanf("%d %d", &n, &m);
  char puzzle[n][m + 1]; for (int i = 0; i < n; i ++) scanf("\n%s", puzzle[i]);

  int dots = 0;
  for (int i = 0; i < n; i ++)
    for (int j = 0; j < m; j ++)
    {
      if (puzzle[i][j] == 'o') dots ++;
      if ((i + j) & 1)
      {
        if (puzzle[i][j] == 'o') addEdge(i*m + j, target, 1);
        else
        {
          addEdge(1*n*m + i*m + j, 3*n*m + i*m + j, 2), addEdge(2*n*m + i*m + j, 3*n*m + i*m + j, 2);
          addEdge(3*n*m + i*m + j, target, 2);
        }
      }
      else
      {
        if (puzzle[i][j] == 'o') addEdge(source, i*m + j, 1);
        else
        {
          addEdge(source, 3*n*m + i*m + j, 2);
          addEdge(3*n*m + i*m + j, 1*n*m + i*m + j, 2), addEdge(3*n*m + i*m + j, 2*n*m + i*m + j, 2);
        }

        for (int k = 0; k < 4; k ++)
        {
          int ii = i + dy[k], jj = j + dx[k];
          if (ii < 0 || jj < 0 || ii >= n || jj >= m) continue;
          if (puzzle[i][j] == 'o')
          {
            if (puzzle[ii][jj] == 'o') addEdge(i*m + j, ii*m + jj, 1);
            else addEdge(i*m + j, (1 + (k % 2))*n*m + ii*m + jj, 1);
          }
          else
          {
            if (puzzle[ii][jj] == 'o') addEdge((1 + (k % 2))*n*m + i*m + j, ii*m + jj, 1);
            else addEdge((1 + (k % 2))*n*m + i*m + j, (1 + (k % 2))*n*m + ii*m + jj, 2);
          }
        }
      }
    }

  int ans = dinic();
  // printf("%d\n", ans);
  printf("%s\n", ans == (n*m - (dots / 2)) ? "Y" : "N");
  RETRIEVE
  {
    int puzz[20][20];
    for (int i = 0; i < n; i ++)
      for (int j = 0; j < m; j ++)
      {
        if (puzzle[i][j] == 'o')
          for (Edge &e: graph[i*m + j])
          {
            if ((((i + j) & 1) && e.flow) || (!((i + j) & 1) && !e.flow))
            {
              int ii = (e.to % (n*m)) / m, jj = (e.to % (n*m)) % m;
              for (int k = 0; k < 4; k ++)
                if (ii == i + dy[k] && jj == j + dx[k])
                  puzz[i][j] = 11+k;
            }
          }
        else
        {
          vector<int> dir;
          for (Edge &e: graph[3*n*m + i*m + j])
            if (e.flow != e.capacity)
            {
              for (Edge &ee: graph[e.to])
                if (ee.flow != ee.capacity)
                {
                  int ii = (ee.to % (n*m)) / m, jj = (ee.to % (n*m)) % m;
                  for (int k = 0; k < 4; k ++)
                    if (ii == i + dy[k] && jj == j + dx[k])
                      dir.push_back(k);
                }
            }
          sort(dir.begin(), dir.end());
          if (dir.size() == 1) puzz[i][j] = 7+dir[0];
          else if (dir[0] % 2 == dir[1] % 2) puzz[i][j] = 1 + (dir[0] % 2);
          else puzz[i][j] = mapDirToCorner[{dir[0], dir[1]}];
        }
      }
    printf("%d %d\n", n, m);
    for (int i = 0; i < n; i ++)
      for (int j = 0; j < m; j ++)
        printf("%d%c", puzz[i][j], j < m - 1 ? ' ' : '\n');
  }
  return(0);
}
