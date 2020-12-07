#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

/* Tutorial:
  You will have a rainbow cycle if you store u and v into two sets:
    a1 = {u, v}, a2 = {u, v}
    u -[a1]> v -[a2]> u

  What if sets where vertices as well? You would have a bipartite graph:
    vertices | sets
    Looking this way, you have a rainbow cylce if you have a cycle in this
    bipartite graph.

    The same exemple as above:
    u - a1
     \ /
      x
     / \
    v - a2

  So, you want: NO CYCLEs, also known as: trees :)

  Since you want to spend the minimum amount of money: the remaining edges
  must have the maximum cost possible, so:
    You want the Maximum Spanning Tree of the bipartite graph

  ans = sumOfAllCosts - mstCost
*/

const int maxN = 1e5, maxNM = 2e5; int m, n;
lli a[maxN], b[maxN];

vector<int> sets[maxN];

struct Edge
{
  int u, v; lli cost;
  bool operator<(const Edge &other) const { return cost > other.cost; }
};
vector<Edge> edges;

int parent[maxNM];
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

int main()
{
  while (scanf("%d %d", &m, &n) != EOF)
  {
    for (int i = 0; i < m; i++)
      scanf("%lld", &a[i]);
    for (int i = 0; i < n; i++)
      scanf("%lld", &b[i]);

    for (int i = 0; i < m; i++)
    {
      int s; scanf("%d", &s);
      sets[i].clear();
      for (int j = 0; j < s; j++)
      {
        int a; scanf("%d", &a); a--;
        sets[i].push_back(a);
      }
    }

    edges.clear();
    lli ans = 0;
    for (int i = 0; i < m; i++)
      for (int j = 0; j < sets[i].size(); j++)
      {
        edges.push_back(Edge{sets[i][j], n + i, a[i] + b[sets[i][j]]});
        ans += a[i] + b[sets[i][j]];
      }
    sort(edges.begin(), edges.end());

    memset(parent, -1, sizeof(parent));
    for (Edge &e: edges)
      if (root(e.u) != root(e.v))
        merge(e.u, e.v), ans -= e.cost;
    printf("%lld\n", ans);
  }
  return 0;
}
