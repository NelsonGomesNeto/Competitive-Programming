#include <bits/stdc++.h>
using namespace std;
#define lli long long int
#define DEBUG if(0)
#define ni (i + dy[k])
#define nj (j + dx[k])
lli inf = 1<<20;
char sea[31][31];
int x, y, p;
int dx[4] = {0, 0, 1, -1}, dy[4] = {1, -1, 0, 0};
int matrixGraph[902 * 2][902 * 2], cap[902], vstd[31][31];

int getCapacity(char place)
{
  if (place == '*') return(1);
  if (place == '.') return(1);
  if (place == '@') return(inf);
  if (place == '#') return(inf);
  return(1);
}

int bfs(vector<int> graph[], int source, int target, int parent[])
{
  int visited[902 * 2]; memset(visited, 0, sizeof(visited));
  deque<int> queue;
  queue.push_back(source);
  visited[source] = 1;
  while (!queue.empty())
  {
    int u = queue.front(); queue.pop_front();
    for (auto v: graph[u])
      if (!visited[v] && matrixGraph[u][v] > 0)
      {
        queue.push_back(v);
        parent[v] = u;
        visited[v] = 1;
      }
  }
  return(visited[target]);
}

int fordFulkerson(vector<int> graph[], int source, int target)
{
  int maxFlow = 0, parent[902 * 2]; memset(parent, -1, sizeof(parent));
  while (bfs(graph, source, target, parent))
  {
    int pathFlow = inf, v = target, u;
    while (v != source)
    {
      u = parent[v];
      pathFlow = min(pathFlow, matrixGraph[u][v]);
      v = parent[v];
    }
    v = target;
    while (v != source)
    {
      DEBUG printf("%d ->", v);
      u = parent[v];
      matrixGraph[u][v] -= pathFlow;
      matrixGraph[v][u] += pathFlow;
      v = parent[v];
    }
    DEBUG printf("%d, Got a path: %d\n", source, pathFlow);
    maxFlow += pathFlow;
  }
  return(maxFlow);
}

int main()
{
  while (scanf("%d %d %d", &y, &x, &p) != EOF)
  {
    memset(matrixGraph, 0, sizeof(matrixGraph));
    for (int i = 0; i < y; i ++)
    {
      getchar();
      scanf("%s", sea[i]);
    }

    DEBUG {
      for (int i = 0; i < y; i ++) printf("%s\n", sea[i]);
      printf("\n");
    }

    vector<int> graph[902 * 2];
    for (int i = 0; i < y; i ++)
      for (int j = 0; j < x; j ++)
      {
        graph[i*x + j + 1].push_back(i*x + j + 1 + 901);
        matrixGraph[i*x + j + 1][i*x + j + 1 + 901] = getCapacity(sea[i][j]);
        graph[i*x + j + 1 + 901].push_back(i*x + j + 1);

        if (sea[i][j] == '*')
        {
          graph[0].push_back(i*x + j + 1);
          matrixGraph[0][i*x + j + 1] = 1;
          graph[i*x + j + 1].push_back(0);
        }
        if (sea[i][j] == '#')
        {
          graph[i*x + j + 1 + 901].push_back(902*2 - 1);
          matrixGraph[i*x + j + 1 + 901][902*2 - 1] = p;
          graph[902*2 - 1].push_back(i*x + j + 1 + 901);
        }

        for (int k = 0; k < 4; k ++)
        {
          if (ni < 0 || ni >= y || nj < 0 || nj >= x || sea[ni][nj] == '~') continue;
          {
            graph[i*x + j + 1 + 901].push_back(ni*x + nj + 1);
            matrixGraph[i*x + j + 1 + 901][ni*x + nj + 1] = inf;
            graph[ni*x + nj + 1].push_back(i*x + j + 1 + 901);
          }
        }

      }

    DEBUG {
      for (int i = 0; i < 902*2; i ++)
      {
        if (graph[i].size() >= 1)
        {
          printf("%d", i);
          for (auto j: graph[i])
          printf(" -> (%d, %d)", j, matrixGraph[i][j]);
          printf("\n");
        }
      }
    }

    int ans = fordFulkerson(graph, 0, 902*2 - 1);
    printf("%d\n", ans);
  }

  return(0);
}

/*if (sea[i][j] == '*')
{
  graph[0].push_back(i*x + j + 1);
  graph[i*x + j + 1].push_back(0);
  matrixGraph[0][i*x + j + 1] = 1;
}
if (sea[i][j] == '#') // Put a mid layer here!
{
  //graph[i*x + j + 1 + 901].push_back(i*x + j + 1);
  graph[i*x + j + 1].push_back(i*x + j + 1 + 901);
  graph[i*x + j + 1 + 901].push_back(902*2 - 1);
  //graph[902*2 - 1].push_back(i*x + j + 1 + 901);
  //int flood = floodFill(i, j); printf("Flood: %d\n", flood);
  matrixGraph[i*x + j + 1][i*x + j + 1 + 901] = p;//p*floodFill(i, j);
  matrixGraph[i*x + j + 1 + 901][902*2 - 1] = inf;
}
if (sea[i][j] != '~')
{
  if (sea[i][j] != '*' && sea[i][j] != '#')
  {
    graph[i*x + j + 1].push_back(i*x + j + 1 + 901);
    matrixGraph[i*x + j + 1][i*x + j + 1 + 901] = sea[i][j] == '.' ? 1 : inf;
  }
  for (int k = 0; k < 4; k ++)
    if (ni >= 0 && ni < y && nj >= 0 && nj < x && (sea[ni][nj] == '.' || sea[ni][nj] == '@' || sea[ni][nj] == '#'))
    {
      if (sea[i][j] != '*')
      {
        graph[i*x + j + 1 + 901].push_back(ni*x + nj + 1);
        matrixGraph[i*x + j + 1 + 901][ni*x + nj + 1] = inf;
      }
      else if (sea[ni][nj] != '*')
      {
        graph[i*x + j + 1].push_back(ni*x + nj + 1);
        matrixGraph[i*x + j + 1][ni*x + nj + 1] = 1;
      }
      if (sea[i][j] == '#')
      {
        graph[i*x + j + 1].push_back(ni*x + nj + 1);
        matrixGraph[i*x + j + 1][ni*x + nj + 1] = inf;
      }

      //graph[ni*x + j].push_back(i*x + j);
      //matrixGraph[i*x + j + 1][ni*x + nj + 1] = 1;//calcCapacity(sea[ni][nj]);
    }*/