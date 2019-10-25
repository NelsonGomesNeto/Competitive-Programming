#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 1e5; int n, m;
struct Edge { int to, back, w; bool important; };
vector<Edge> graph[maxN];
vector<pair<pair<int, pair<int, int>>, pair<int, int>>> edges, mstEdges;

int parent[maxN];
int root(int u)
{
  return parent[u] < 0 ? u : parent[u] = root(parent[u]);
}
bool isSameSet(int u, int v) { return root(u) == root(v); }
void merge(int u, int v)
{
  u = root(u), v = root(v);
  if (u == v) return;
  if (parent[u] > parent[v]) swap(u, v);
  parent[u] += parent[v];
  parent[v] = u;
}

int main()
{
  memset(parent, -1, sizeof(parent));
  scanf("%d %d", &n, &m);
  for (int i = 0; i < m; i ++)
  {
    int u, v, w; scanf("%d %d %d", &u, &v, &w); u --, v --;
    graph[u].push_back({v, (int) graph[v].size(), w, false});
    graph[v].push_back({u, (int) graph[u].size() - 1, w, false});
    edges.push_back({{w, {(int) graph[u].size() - 1, (int) graph[v].size() - 1}}, {u, v}});
  }
  sort(edges.begin(), edges.end());

  int mstCost = 0;
  for (int i = 0; i < m; i ++)
    if (!isSameSet(edges[i].second.first, edges[i].second.second))
    {
      merge(edges[i].second.first, edges[i].second.second);
      mstCost += edges[i].first.first;
      mstEdges.push_back(edges[i]);
    }

  int ans = 0;
  for (int i = 0; i < mstEdges.size(); i ++)
  {
    bool can1 = false, can2 = false;
    for (auto v: graph[mstEdges[i].second.first])
      if (v.to != mstEdges[i].second.second && v.w <= mstEdges[i].first.first && !v.important)
        can1 = true;
    for (auto v: graph[mstEdges[i].second.second])
      if (v.to != mstEdges[i].second.first && v.w <= mstEdges[i].first.first && !v.important)
        can2 = true;
    bool can = min(can1, can2);
    ans += !can;
    if (!can) graph[mstEdges[i].second.first][mstEdges[i].first.second.first].important = graph[mstEdges[i].second.second][mstEdges[i].first.second.second].important = true;
    // if (!can) printf("%d | %d %d\n", mstEdges[i].first.first, mstEdges[i].second.first + 1, mstEdges[i].second.second + 1);
  }
  printf("%d\n", ans);

  return 0;
}