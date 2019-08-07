#include <bits/stdc++.h>
using namespace std;

const int maxN = 1e5; int n, q;
int parent[maxN];
int biggest = 1, smallest = 1;
int sizeAmounts[maxN + 1];
set<int> sizes;
int root(int u)
{
  if (parent[u] < 0) return(u);
  return(parent[u] = root(parent[u]));
}
int setSize(int u)
{
  return(-1 * parent[root(u)]);
}
void merge(int u, int v)
{
  u = root(u), v = root(v);
  if (u == v) return;
  if (parent[v] < parent[u]) swap(u, v);

  int usize = setSize(u), vsize = setSize(v);
  sizeAmounts[usize] --, sizeAmounts[vsize] --;
  if (!sizeAmounts[usize]) sizes.erase(usize);
  if (usize != vsize && !sizeAmounts[vsize]) sizes.erase(vsize);

  parent[u] += parent[v];
  parent[v] = u;

  int newsize = setSize(u);
  biggest = max(biggest, newsize);
  if (!sizeAmounts[newsize]) sizes.insert(newsize);
  sizeAmounts[newsize] ++;
  smallest = *sizes.begin();
}

int main()
{
  memset(parent, -1, sizeof(parent));
  scanf("%d %d", &n, &q);
  sizeAmounts[1] = n, sizes.insert(1);

  for (int i = 0, u, v; i < q; i ++)
  {
    scanf("%d %d", &u, &v); u --, v --;
    merge(u, v);
    printf("%d\n", biggest - smallest);
  }

  return(0);
}