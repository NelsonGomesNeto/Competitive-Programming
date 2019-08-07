#include <stdio.h>
#include <string.h>

void conexAux(int graph[][7], int source, int visited[])
{
  if (visited[source]) return;
  visited[source] = 1;
  int i;
  for (i = 0; i < 7; i ++)
    if (graph[source][i])
      conexAux(graph, i, visited);
}

int conex(int graph[][7], int pieces[])
{
  int i, j;
  for (i = 0; i < 7; i ++)
    if (pieces[i])
    {
      int visited[7]; memset(visited, 0, sizeof(visited));
      conexAux(graph, i, visited);
      for (j = 0; j < 7; j ++) if (pieces[j] && !visited[j]) return(0);
      return(1);
    }
  return(0);
}

/*
You can model this problem as a graph, were each piece is an edge. Therefore, asking if there is a way to use every edge is essentially the same as asking if there is an Eulerian Path within the graph we made with the Dominos. So:
if (graph isn't conex) we can't even connect some pieces: CAN'T
if (graph has more then two vertices with odd degree) it's not possible to build an Eulerian Path: CAN'T
otherwise we either have a 0 odd degree (a cycle) ou a 2 odd degree (a path): CAN
*/

int main()
{
  int n, r = 1;
  while (scanf("%d", &n) != EOF && n)
  {
    int graph[7][7]; memset(graph, 0, sizeof(graph));
    int pieces[7]; memset(pieces, 0, sizeof(pieces));
    int u, v, i;
    for (i = 0; i < n; i ++)
    {
      scanf("%d %d", &u, &v);
      graph[u][v] = graph[v][u] = 1;
      pieces[u] ++; pieces[v] ++;
    }
    int odd = 0;
    for (i = 0; i < 7; i ++) odd += pieces[i] & 1;
    printf("Teste %d\n%s\n\n", r ++, (odd > 2 || !conex(graph, pieces)) ? "nao" : "sim");
  }
  return(0);
}
