#include <bits/stdc++.h>
int inf = INT_MAX / 3;

int **floydWarshall(int **graph, int size)
{
  int **dist = (int**) malloc((size + 1) * sizeof(int*));
  for (int i = 0; i <= size; i ++)
  {
    dist[i] = (int*) malloc((size + 1) * sizeof(int));
    for (int j = 0; j <= size; j ++)
      dist[i][j] = graph[i][j];
  }

  for (int k = 0; k <= size; k ++)
    for (int i = 0; i <= size; i ++)
      for (int j = 0; j <= size; j ++)
        if (dist[i][k] + dist[k][j] < dist[i][j])
          dist[i][j] = dist[i][k] + dist[k][j];

  return(dist);
}

int main()
{
  int run = 0, cities, connections;
  while (scanf("%d %d", &cities, &connections) && !(cities == 0 && connections == 0))
  {
    if (run > 0) printf("\n");

    int **graph = (int**) malloc((cities + 1) * sizeof(int*));
    for (int i = 0; i <= cities; i ++)
    {
      graph[i] = (int*) malloc((cities + 1) * sizeof(int));
      for (int j = 0; j <= cities; j ++)
        graph[i][j] = inf;
    }

    int u, v, c;
    for (int i = 0; i < connections; i ++)
    {
      scanf("%d %d %d", &u, &v, &c);
      if (graph[v][u] != inf)
      {
        graph[u][v] = 0;
        graph[v][u] = 0;
      }
      else
        graph[u][v] = c;
    }

    int **dist = floydWarshall(graph, cities);
    int queries; scanf("%d", &queries);
    int begin, end;
    for (int i = 0; i < queries; i ++)
    {
      scanf("%d %d", &begin, &end);
      if (dist[begin][end] == inf)
        printf("Nao e possivel entregar a carta\n");
      else
        printf("%d\n", dist[begin][end]);
    }

    run ++;
    free(graph); free(dist);
  }
  return(0);
}