#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 2e5; int n;
// |V| == |E|
// it's basically a graph

struct Edge
{
  int u, v;
  void read() { scanf("%d %d", &u, &v); u--, v--; }
};
Edge edges[maxN], cycleEdge;
vector<int> graph[maxN];

int parents[maxN];
int root(int u)
{
  return parents[u] < 0 ? u : parents[u] = root(parents[u]);
}
void merge(int u, int v)
{
  u = root(u), v = root(v);
  if (u == v) return;
  if (parents[u] > parents[v]) swap(u, v);
  parents[u] += parents[v];
  parents[v] = u;
}

bool isCycleVertex[maxN];
vector<int> cycleVertices;
bool foundCycle(int origin = cycleEdge.u, int u = cycleEdge.v, int prv = cycleEdge.u)
{
  if (u == origin) return true;
  for (int v: graph[u])
    if (v != prv)
      if (foundCycle(origin, v, u))
      {
        cycleVertices.push_back(v);
        return true;
      }
  return false;
}
int subtreeSize[maxN];
void calcSubtreeSize(int u, int prv = -1)
{
  subtreeSize[u] = 1;
  for (int v: graph[u])
    if (v != prv && !isCycleVertex[v])
    {
      calcSubtreeSize(v, u);
      subtreeSize[u] += subtreeSize[v];
    }
}

int main()
{
  int t; scanf("%d", &t);
  for (int tt = 1; tt <= t; tt++)
  {
    scanf("%d", &n);
    fill(parents, parents+n, -1);
    for (int i = 0; i < n; i++)
      graph[i].clear();

    for (int i = 0; i < n; i++)
    {
      edges[i].read();
      if (root(edges[i].u) == root(edges[i].v))
        cycleEdge = edges[i];
      else
        merge(edges[i].u, edges[i].v);
      graph[edges[i].u].push_back(edges[i].v), graph[edges[i].v].push_back(edges[i].u);
    }

    memset(isCycleVertex, false, sizeof(isCycleVertex));
    cycleVertices.clear();
    foundCycle();
    cycleVertices.push_back(cycleEdge.v);
    for (int u: cycleVertices) isCycleVertex[u] = true;

    DEBUG for (int i = 0; i < cycleVertices.size(); i++) printf("%d%c", cycleVertices[i] + 1, i < cycleVertices.size() - 1 ? ' ' : '\n');

    for (int u: cycleVertices)
      calcSubtreeSize(u);

    lli ans = 0;
    for (int u: cycleVertices)
    {
      ans += 2LL * subtreeSize[u] * (n - subtreeSize[u]);
      ans += (lli)subtreeSize[u] * (subtreeSize[u] - 1);
      DEBUG printf("\t\t%d %d\n", u + 1, subtreeSize[u]);
    }
    ans >>= 1LL;
    DEBUG printf("\t%d\n", (int)cycleVertices.size());

    printf("%lld\n", ans);
  }
  return 0;
}
