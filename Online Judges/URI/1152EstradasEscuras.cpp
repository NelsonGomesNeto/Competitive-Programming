#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 2e5; int n, m;
struct Edge
{
  int u, v, c;
  void read() { scanf("%d %d %d", &u, &v, &c); }
  bool operator<(const Edge &other) const { return c < other.c; }
};
Edge edges[maxN];

int parent[maxN];
int root(int u)
{
  return parent[u] < 0 ? u : parent[u] = root(parent[u]);
}
bool sameSet(int u, int v)
{
  return root(u) == root(v);
}
void merge(int u, int v)
{
  if ((u = root(u)) == (v = root(v))) return;
  if (parent[u] > parent[v]) swap(u, v);
  parent[u] += parent[v];
  parent[v] = u;
}

int main()
{
  while (scanf("%d %d", &n, &m) && !(!n && !m))
  {
    for (int i = 0; i < n; i++) parent[i] = -1;
    for (int i = 0; i < m; i++)
      edges[i].read();
    sort(edges, edges+m);

    lli ans = 0;
    for (int i = 0; i < m; i++)
      ans += edges[i].c;
    for (int i = 0; i < m; i++)
      if (!sameSet(edges[i].u, edges[i].v))
        ans -= edges[i].c, merge(edges[i].u, edges[i].v);
    printf("%lld\n", ans);
  }
  return 0;
}