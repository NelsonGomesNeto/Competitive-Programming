#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 2e3; int n, m;
struct Edge
{
  int u, v, cost; bool used;
  bool operator<(const Edge &other) { return cost < other.cost; }
};
vector<Edge> edges;
int a[maxN], cnt[maxN];

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

int main()
{
  int t; scanf("%d", &t);
  while (t --)
  {
    memset(parent, -1 ,sizeof(parent)), memset(cnt, 0, sizeof(cnt));
    edges.clear();

    scanf("%d %d", &n, &m);
    for (int i = 0; i < n; i ++)
      scanf("%d", &a[i]);

    for (int i = 0; i < n; i ++)
      for (int j = i + 1; j < n; j ++)
        edges.push_back({i, j, a[i] + a[j], false});
    sort(edges.begin(), edges.end());

    bool can = true;
    int ans = 0, done = 0;
    for (Edge &e: edges)
      if (root(e.u) != root(e.v) && done < m && cnt[e.u] < 2 && cnt[e.v] < 2)
      {
        merge(e.u, e.v), e.used = true, cnt[e.u] ++, cnt[e.v] ++;
        ans += e.cost, done ++;
      }
    for (int i = 0, r = 0; i < n; i ++)
    {
      if (parent[i] < 0)
        r ++;
      if (r > 1 && done == m)
        can = false;
    }
    for (Edge &e: edges)
      if (!e.used && done < m && cnt[e.u] < 2 && cnt[e.v] < 2)
        ans += e.cost, e.used = true, cnt[e.u] ++, cnt[e.v] ++, done ++;
    for (Edge &e: edges)
      if (!e.used && done < m)
        ans += e.cost, e.used = true, done ++;
    for (int i = 0; i < n; i ++)
      if (cnt[i] < 2)
        can = false;

    if (!can) printf("-1\n");
    else
    {
      printf("%d\n", ans);
      for (Edge &e: edges)
        if (e.used)
          printf("%d %d\n", e.u + 1, e.v + 1);
    }
  }
  return 0;
}