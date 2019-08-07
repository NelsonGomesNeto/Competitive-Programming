#include <bits/stdc++.h>
using namespace std;

const int maxN = 1e5; int n, q;

int parent[maxN];
int root(int u)
{
  if (parent[u] < 0) return(u);
  return(parent[u] = root(parent[u]));
}
void merge(int u, int v)
{
  u = root(u), v = root(v);
  if (u == v) return;
  if (parent[v] < parent[u]) swap(u, v);
  parent[u] += parent[v];
  parent[v] = u;
}
int setSize(int u)
{
  return(-1 * parent[root(u)]);
}

int main()
{
  int t; scanf("%d", &t);
  while (t --)
  {
    scanf("%d %d", &n, &q);
    memset(parent, -1, sizeof(int)*n);
    int no = 0, yes = 0;
    while (q --)
    {
      char op; int u, v; scanf(" %c %d %d", &op, &u, &v); u --, v --;
      if (op == 'J') merge(u, v);
      else
      {
        if (root(u) == root(v)) yes ++;
        else no ++;
      }
    }
    printf("%d %d\n", yes, no);
  }
  return(0);
}