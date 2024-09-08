#include <bits/stdc++.h>
#define DEBUG if(0)
using namespace std;
int matrixGraph[54][54];
int inf = 1<<20;

int bfs(vector<int> graph[], int source, int target, int parent[])
{
  int visited[54]; memset(visited, 0, sizeof(visited));
  deque<int> queue;
  queue.push_back(source);
  visited[source] = 1;
  parent[source] = 1;
  while (!queue.empty())
  {
    int u = queue.front(); queue.pop_front();
    for (auto v: graph[u])
    {
      if (!visited[v] && matrixGraph[u][v] > 0)
      {
        queue.push_back(v);
        parent[v] = u;
        visited[v] = 1;
      }
    }
  }
  return(visited[target]);
}

int fordFulkerson(vector<int> graph[], int source, int target)
{
  int maxFlow = 0, parent[54]; memset(parent, -1, sizeof(parent));
  while (bfs(graph, source, target, parent))
  {
    int pathFlow = inf;
    int v = target, u;
    while (v != source)
    {
      u = parent[v];
      pathFlow = min(pathFlow, matrixGraph[u][v]);
      v = parent[v];
    }
    v = target;
    while (v != source)
    {
      u = parent[v];
      matrixGraph[u][v] -= pathFlow;
      matrixGraph[v][u] += pathFlow;
      v = parent[v];
    }
    maxFlow += pathFlow;
  }
  return(maxFlow);
}

void format(string& s)
{
  for (int i = 0; i < s.size(); i ++)
    s[i] = tolower(s[i]);
  s[0] = toupper(s[0]);
}

int main()
{
  int tests, run = 1; scanf("%d", &tests);
  while (run ++ <= tests)
  {
    memset(matrixGraph, 0, sizeof(matrixGraph));
    int problems; scanf("%d", &problems);
    vector<string> name[26];
    for (int i = 0; i < problems; i ++)
    {
      int k; scanf("%d", &k);
      string candidate;
      for (int j = 0; j < k; j ++)
      {
        getchar();
        cin >> candidate;
        format(candidate);
        name[i].push_back(candidate);
      }
      DEBUG {
        for (auto j: name[i])
          cout << j << ' ';
        cout << endl;
      }
    }

    vector<int> graph[54];
    for (int i = 1; i <= problems; i ++)
    {
      graph[0].push_back(i);
      graph[i].push_back(0);
      matrixGraph[0][i] = 1;
    }

    for (int i = 27; i < 53; i ++)
    {
      graph[i].push_back(53);
      graph[53].push_back(i);
      matrixGraph[i][53] = 1;
    }

    for (int i = 0; i < problems; i ++)
    {
      for (auto j: name[i])
      {
        graph[i + 1].push_back(j[0] - 'A' + 27);
        graph[j[0] - 'A' + 27].push_back(i + 1);
        matrixGraph[i + 1][j[0] - 'A' + 27] = 1;
      }
    }

    DEBUG {
      for (int i = 0; i <= 53; i ++)
      {
        printf("%d ->", i);
        for (auto j: graph[i])
          printf(" %d", j);
        printf("\n");
      }
      printf("\n");
    }

    int ans = fordFulkerson(graph, 0, 53);

    DEBUG {
      for (int i = 0; i < 54; i ++)
      {
        printf("%2d -> ", i);
        for (int j = 0; j < 54; j ++)
          if (matrixGraph[i][j])
            printf("%2d -> ", j);
        printf("\n");
      }
    }

    printf("Case #%d:\n", run - 1);
    for (int i = 27; i < 53; i ++)
      for (int j = 1; j < 27; j ++)
        if (matrixGraph[i][j])
          for (auto k: name[j - 1])
            if (k[0] - 'A' + 27 == i)
              cout << k << endl;

    DEBUG printf("%d\n", ans);

  }
  return(0);
}