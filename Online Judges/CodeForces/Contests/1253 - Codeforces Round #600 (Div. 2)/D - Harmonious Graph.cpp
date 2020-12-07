#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 2e5; int n, m;
int parent[maxN], minimum[maxN], maximum[maxN];
int root(int u)
{
  return parent[u] < 0 ? u : parent[u] = root(parent[u]);
}
void merge(int u, int v)
{
  int ou = u, ov = v;
  if ((u = root(u)) == (v = root(v))) return;
  if (parent[u] > parent[v]) swap(u, v);
  minimum[u] = min({minimum[u], minimum[v], ou, ov});
  maximum[u] = max({maximum[u], maximum[v], ou, ov});
  parent[u] += parent[v];
  parent[v] = u;
}
int setSize(int u)
{
  return -parent[root(u)];
}

int main()
{
  while (scanf("%d %d", &n, &m) != EOF)
  {
    memset(parent, -1, sizeof(parent));
    for (int i = 0; i < n; i ++)
      minimum[i] = maximum[i] = i;

    for (int i = 0; i < m; i ++)
    {
      int u, v; scanf("%d %d", &u, &v); u --, v --;
      merge(u, v);
    }

    int ans = 0;
    for (int i = n - 1; i >= 0; i --)
    {
      if (maximum[root(i)] - minimum[root(i)] + 1 != setSize(i))
      {
        DEBUG printf("%d %d %d %d %d\n", i + 1, root(i) + 1, minimum[root(i)] + 1, maximum[root(i)] + 1, setSize(i));
        for (int j = minimum[root(i)], end = maximum[root(i)]; j <= end; j ++)
          if (root(j) != root(i))
            merge(i, j), ans ++;
      }
    }
    printf("%d\n", ans);
  }
  return 0;
}
