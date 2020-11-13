#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 1e5, maxQ = 1e7; int n, q, sq, mk;
const lli mod = 1e9 + 7;
struct Tile
{
  lli x, y;
  void read() { scanf("%lld %lld", &x, &y); }
  lli dist(Tile other) { return abs(x - other.x) + abs(y - other.y); }
};
Tile tiles[maxN];
lli as, bs, cs, at, bt, ct, ak, bk, ck;
struct Query
{
  int s, t, idx; lli k;
  void read(int i) { scanf("%d %d %lld", &s, &t, &k); idx = i; }
  bool operator<(const Query &other) const { return k < other.k; }
};
Query queries[maxQ];
bool ans[maxQ];

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
  while (scanf("%d %d %d %d", &n, &q, &sq, &mk) != EOF)
  {
    for (int i = 0; i < n; i++)
      tiles[i].read();

    scanf("%lld %lld %lld %lld %lld %lld %lld %lld %lld", &as, &bs, &cs, &at, &bt, &ct, &ak, &bk, &ck);
    DEBUG printf("%lld %lld %lld %lld %lld %lld %lld %lld %lld\n", as, bs, cs, at, bt, ct, ak, bk, ck);
    for (int i = 0; i < sq; i++)
      queries[i].read(i);
    for (int i = sq; i < q; i++)
    {
      queries[i].s = (as * queries[i - 1].s + bs * queries[i - 2].s + cs) % n + 1;
      queries[i].t = (at * queries[i - 1].t + bt * queries[i - 2].t + ct) % n + 1;
      queries[i].k = (ak * queries[i - 1].k + bk * queries[i - 2].k + ck) % mk;
      queries[i].idx = i;
    }
    for (int i = 0; i < q; i++)
    {
      queries[i].s--, queries[i].t--;
      DEBUG printf("%d %d %lld\n", queries[i].s + 1, queries[i].t + 1, queries[i].k);
    }
    sort(queries, queries+q);

    vector<pair<lli, pair<int, int>>> edges;
    for (int i = 0; i < n; i++)
      for (int j = i + 1; j < n; j++)
        edges.push_back({tiles[i].dist(tiles[j]) - 1, {i, j}});
    sort(edges.begin(), edges.end());

    memset(parent, -1, sizeof(parent));
    for (auto &e: edges)
    {
      merge(e.second.first, e.second.second);
      DEBUG printf("%d %d - %d\n", e.second.first + 1, e.second.second + 1, root(e.second.first) == root(e.second.second));
      for (int qi = 0; qi < q; qi++)
        if (e.first <= queries[qi].k)
          ans[queries[qi].idx] |= root(queries[qi].s) == root(queries[qi].t);
    }

    lli res = 0;
    for (lli i = 0, p = 2; i < q; i++, p = p * 2LL % mod)
    {
      DEBUG printf("%lld - %d\n", i, ans[i]);
      res = (res + p * ans[i] % mod) % mod;
    }
    printf("%lld\n", res);
  }
  return 0;
}