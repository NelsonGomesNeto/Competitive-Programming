#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

struct DSU
{
  int size;
  vector<int> parents;
  DSU() { parents.clear(); }
  DSU(int sz) : size(sz) { init(); }
  void init() { parents.resize(size, -1); }
  int root(int u) { return parents[u] < 0 ? u : parents[u] = root(parents[u]); }
  void merge(int u, int v)
  {
    u = root(u), v = root(v);
    if (u == v) return;
    if (parents[u] > parents[v]) swap(u, v);
    parents[u] += parents[v];
    parents[v] = u;
  }
  int setSize(int u) { return -parents[root(u)]; }
  bool sameSet(int u, int v) { return root(u) == root(v); }
};

const lli inf = 1e16;
const int kMaxN = 8;
int n, m;
lli k;
struct Edge {
  int u, v;
  lli w;
  void Read() {
    scanf("%d %d %lld", &u, &v, &w);
    --u, --v;
  }
};
vector<Edge> edges;

lli minimum_cost = inf;
void Solve(int i = 0, int chosen = 0, lli cost = 0, DSU dsu = DSU(n)) {
  if (chosen == n - 1) {
    DEBUG printf("\t%d %lld %lld\n", i, cost, cost % k);
    minimum_cost = min(minimum_cost, cost % k);
    return;
  }
  if (i == m) return;

  Solve(i + 1, chosen, cost, dsu);
  if (!dsu.sameSet(edges[i].u, edges[i].v)) {
    dsu.merge(edges[i].u, edges[i].v);
    Solve(i + 1, chosen + 1, cost + edges[i].w, dsu);
  }
}

int main() {
  while (~scanf("%d %d %lld", &n, &m, &k)) {
    edges.resize(m);
    for (Edge& e : edges) e.Read();

    minimum_cost = inf;
    Solve();
    printf("%lld\n", minimum_cost);
  }
  return 0;
}
