#include <bits/stdc++.h>
using namespace std;

const int maxN = 1e5, maxM = 1e5; int n, m;
vector<pair<int, pair<int, int>>> edges;
bool notHack[maxN];

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
  memset(parent, -1, sizeof(parent));
  scanf("%d %d", &n, &m);
  for (int i = 0, u, v; i < m; i ++)
  {
    scanf("%d %d", &u, &v); u --, v --;
    if (u > v) swap(u, v);
    edges.push_back({i, {u, v}});
  }
  reverse(edges.begin(), edges.end());

  // No matter which edges you choose, you will always end up with a tree
  // So... Just try to keep the last edges, and hack the ones that are left
  for (auto &e: edges)
  {
    if (root(e.second.first) == root(e.second.second)) continue;
    merge(e.second.first, e.second.second);
    notHack[e.first] = true;
  }

  printf("%d\n", m - n + 1);
  for (int i = 0; i < m; i ++)
    if (!notHack[i])
      printf("%d\n", i + 1);

  return(0);
}