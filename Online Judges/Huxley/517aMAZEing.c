#include <stdio.h>
#include <string.h>
#define DEBUG if(0)
int parent[1000000];

int root(int v)
{
  if (parent[v] < 0)
    return(v);
  else
  {
    parent[v] = root(parent[v]);
    return(parent[v]);
  }
}

int isSameSet(int v, int u)
{
  return(root(v) == root(u));
}

void merge(int v, int u)
{
  v = root(v);
  u = root(u);
  if (v == u) return;

  if (parent[u] < parent[v])
  {
    int aux = parent[u];
    parent[u] = parent[v];
    parent[v] = aux;
  }
  parent[v] += parent[u];
  parent[u] = v;
}

int setSize(int v)
{
  return(-1 * parent[root(v)]);
}

int main()
{
  int size, originalSize, walls, queries, run = 0;
  while (scanf("%d %d %d", &size, &walls, &queries) != EOF)
  {
    originalSize = size;
    if (run == 1) printf("\n");
    memset(parent, -1, sizeof(parent));

    size = (2 * size) - 1;

    // Execute unions
    int wall, i;
    for (i = 0; i < walls; i ++)
    {
      scanf("%d", &wall);
      if ((2*wall + 1) / size & 1)
      {
        merge((((((2*wall + 1) / size) - 1) / 2) * originalSize) + (((2*wall + 1) % size) / 2),
              (((((2*wall + 1) / size) - 1) / 2) * originalSize) + (((2*wall + 1) % size) / 2) + originalSize);
        //printf("%d %d %d\n", (2*wall + 1) / size & 1,
        //(((((2*wall + 1) / size) - 1) / 2) * originalSize) + (((2*wall + 1) % size) / 2),
        //(((((2*wall + 1) / size) - 1) / 2) * originalSize) + (((2*wall + 1) % size) / 2) + originalSize);
      } // Wall is on odd y
      else
      {
        merge((((((2*wall + 1) / size) + 1) / 2) * originalSize) + ((((2*wall + 1) % size) - 1) / 2),
              (((((2*wall + 1) / size) + 1) / 2) * originalSize) + ((((2*wall + 1) % size) - 1) / 2) + 1);
        //printf("%d %d %d\n", (2*wall + 1) / size & 1,
        //(((((2*wall + 1) / size) + 1) / 2) * originalSize) + ((((2*wall + 1) % size) - 1) / 2),
        //(((((2*wall + 1) / size) + 1) / 2) * originalSize) + ((((2*wall + 1) % size) - 1) / 2) + 1);
      }
    }

    // Queries
    int start, end;
    for (i = 0; i < queries; i ++)
    {
      scanf("%d %d", &start, &end);
      printf("%d.%d\n", i + 1, isSameSet(start, end));
    }
    run = 1;
  }

  return(0);
}