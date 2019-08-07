#include <stdio.h>
#include <string.h>
#define DEBUG if(0)
int disjointSets = 0;

int root(int parent[], int u)
{
  if (parent[u] < 0) return(u);
  parent[u] = root(parent, parent[u]);
  return(parent[u]);
}

int isSameSet(int parent[], int u, int v)
{
  return(root(parent, u) == root(parent, v));
}

void merge(int parent[], int u, int v)
{
  v = root(parent, v); u = root(parent, u);
  if (u == v) return;

  if (parent[v] > parent[u])
  {
    int aux = parent[u];
    parent[u] = parent[v];
    parent[v] = aux;
  }

  disjointSets --;
  parent[v] += parent[u];
  parent[u] = v;
}

int setSize(int parent[], int u)
{
  return(-1 * parent[root(parent, u)]);
}

int main()
{
  int friends, relations; scanf("%d %d", &friends, &relations);
  int parent[friends + 1]; memset(parent, -1, sizeof(parent));
  disjointSets = friends;

  int i, u, v;
  for (i = 0; i < relations; i ++)
  {
    scanf("%d %d", &u, &v);
    merge(parent, u, v);
  }

  // int groups = 0;
  // for (i = 1; i <= friends; i ++)
  // {
  //   DEBUG printf("(%d, %d)\n", i, parent[i]);
  //   groups += parent[i] < 0;
  // }

  printf("%d\n", disjointSets);

  return(0);
}