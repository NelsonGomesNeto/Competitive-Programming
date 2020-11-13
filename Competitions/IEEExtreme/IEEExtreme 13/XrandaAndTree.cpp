#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 1e5; int n;
const lli mod = 1e9 + 7;

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
int setSize(int u) { return -parent[root(u)]; }

vector<pair<lli, pair<int, int>>> edges;

int main()
{
  memset(parent, -1, sizeof(parent));
  scanf("%d", &n);
  for (int i = 1; i < n; i ++)
  {
    int u, v; lli w; scanf("%d %d %lld", &u, &v, &w); u --, v --;
    edges.push_back({w, {u, v}});
  }
  sort(edges.begin(), edges.end());

  lli ans = 0;
  for (auto &e: edges)
  {
    lli a = setSize(e.second.first), b = setSize(e.second.second);
    merge(e.second.first, e.second.second);
    ans = (ans + e.first * (a * b % mod) % mod) % mod;
  }
  printf("%lld\n", ans);

  return 0;
}