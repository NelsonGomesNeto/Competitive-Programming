#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

/* Tutorial:
  DSU

  If you sort the edges ascendly (lower to higher):
    You will guarantee the second rule

  Now using DSU, each set (vertex group) will have an array "total"
    total[k] is the amount of ways you can split this set into k sets
    At first total[1] = 1 for all sets

    When merging a and b:
      for i in [1 : a.total.size()]:
        for j in [1 : b.total.size()]:
          newTotal[i + j] += a.total[i] * b.total[j]

      But newTotal[1] will only be 1 if this set is ready. It is ready if all
      it's edges have been processed (is a clique). So you will also have to
      store the amount of edges each set has.
*/

const int maxN = 15e2; int n;
const lli mod = 998244353;
int a[maxN][maxN];

struct Edge
{
  int u, v, cost;
  bool operator<(const Edge &other) const { return cost < other.cost; }
};
vector<Edge> edges;

int parent[maxN], setEdges[maxN];
vector<lli> memo[maxN];
int root(int u)
{
  return parent[u] < 0 ? u : parent[u] = root(parent[u]);
}
int setSize(int u)
{
  return -parent[root(u)];
}
bool isClique(int u)
{
  return setEdges[root(u)] == (setSize(u) * (setSize(u) - 1)) >> 1;
}
void merge(int u, int v)
{
  if ((u = root(u)) == (v = root(v)))
  {
    setEdges[u]++;
    if (isClique(u)) memo[u][1] = 1;
    return;
  }

  if (parent[u] > parent[v]) swap(u, v);
  parent[u] += parent[v];
  setEdges[u] += setEdges[v] + 1;
  parent[v] = u;

  vector<lli> aux(memo[u].size() + memo[v].size() - 1);
  aux[1] = isClique(u);
  for (int i = 1; i < memo[u].size(); i++)
    for (int j = 1; j < memo[v].size(); j++)
      aux[i + j] = (aux[i + j] + memo[u][i] * memo[v][j] % mod) % mod;
  memo[u] = aux;
}

int main()
{
  int tt = 0;
  while (scanf("%d", &n) != EOF)
  {
    if (tt++) printf("\n");

    for (int i = 0; i < n; i++)
      for (int j = 0; j < n; j++)
        scanf("%d", &a[i][j]);

    edges.clear();
    for (int i = 0; i < n; i++)
      for (int j = i + 1; j < n; j++)
        edges.push_back(Edge{i, j, a[i][j]});
    sort(edges.begin(), edges.end());

    DEBUG
      for (Edge &e: edges)
        printf("%d %d | %d\n", e.u + 1, e.v + 1, e.cost);

    memset(parent, -1, sizeof(parent));
    memset(setEdges, 0, sizeof(setEdges));
    for (int i = 0; i < n; i++)
    {
      memo[i].resize(2);
      memo[i][1] = 1;
    }
    for (Edge &e: edges)
    {
      merge(e.u, e.v);
    }

    vector<lli> &ans = memo[root(0)];
    for (int i = 1; i < ans.size(); i++)
      printf("%lld%c", ans[i], "\n "[i < ans.size() - 1]);
  }
  return 0;
}