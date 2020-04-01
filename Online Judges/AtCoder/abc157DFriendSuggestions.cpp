#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 1e5; int n, m, k;

int parent[maxN];
int root(int u)
{
  return parent[u] < 0 ? u : parent[u] = root(parent[u]);
}
void merge(int u, int v)
{
  if ((u = root(u)) == (v = root(v))) return;
  if (parent[u] > parent[v]) swap(u, v);
  parent[u] += parent[v];
  parent[v] = u;
}
bool sameSet(int u, int v)
{
  return root(u) == root(v);
}
int setSize(int u)
{
  return -parent[root(u)];
}

set<int> friends[maxN], blocks[maxN];
int ans[maxN];

int unionSize(int u)
{
  int sz = friends[u].size() + blocks[u].size();
  for (int v: blocks[u])
    if (!sameSet(u, v))
      sz --;
  return sz;
}

int main()
{
  while (scanf("%d %d %d", &n, &m, &k) != EOF)
  {
    memset(parent, -1, sizeof(parent));
    for (int i = 0; i < n; i ++)
      friends[i].clear(), blocks[i].clear();

    for (int i = 0; i < m; i ++)
    {
      int u, v; scanf("%d %d", &u, &v); u --, v --;
      friends[u].insert(v), friends[v].insert(u);
      merge(u, v);
    }

    for (int i = 0; i < k; i ++)
    {
      int u, v; scanf("%d %d", &u, &v); u --, v --;
      blocks[u].insert(v), blocks[v].insert(u);
    }

    for (int i = 0; i < n; i ++)
      ans[i] = setSize(i) - unionSize(i) - 1;

    for (int i = 0; i < n; i ++)
      printf("%d%c", ans[i], i < n - 1 ? ' ' : '\n');
  }
  return 0;
}