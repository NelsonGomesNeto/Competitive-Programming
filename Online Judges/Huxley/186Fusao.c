#include <stdio.h>
#include <string.h>

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
  if (v == u) return;

  if (parent[v] > parent[u])
  {
    int aux = parent[u];
    parent[u] = parent[v];
    parent[v] = aux;
  }

  parent[v] += parent[u];
  parent[u] = v;
}

int setSize(int parent[], int u)
{
  return(-1 * parent[root(parent, u)]);
}

int main()
{
  int banks, queries; scanf("%d %d", &banks, &queries);
  int parent[banks + 1]; memset(parent, -1, sizeof(parent));

  int i, u, v; char c;
  for (i = 0; i < queries; i ++)
  {
    getchar();
    scanf("%c %d %d", &c, &u, &v);
    if (c == 'C')
      printf("%c\n", isSameSet(parent, u, v) ? 'S' : 'N');
    else
      merge(parent, u, v);
  }

  return(0);
}