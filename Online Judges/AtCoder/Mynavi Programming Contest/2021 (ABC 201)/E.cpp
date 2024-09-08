#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 2e5; int n;
const lli mod = 1e9 + 7;
struct Edge
{
  int u, v; lli w;
};
vector<Edge> tree[maxN];

lli subtree[maxN][2];
void dfs(int bit, int curr = 0, int u = 0, int prv = -1)
{
  subtree[u][0] = subtree[u][1] = 0;

  assert(curr >= 0 && curr <= 1);
  // if (u)
    subtree[u][curr]++;

  for (Edge &e: tree[u])
    if (e.v != prv)
    {
      subtree[u][0] += subtree[e.v][0];
      subtree[u][1] += subtree[e.v][1];
      dfs(bit, curr ^ ((e.w >> bit) & 1), e.v, u);
    }
}

lli dfs2(int bit, int curr = 0, int u = 0, int prv = -1)
{
  assert(curr >= 0 && curr <= 1);

  lli total = 0;
  // if (prv != -1)
  {
    total = (total
      // + subtree[u][0] + (subtree[0][0] - subtree[u][0]) % mod
      + subtree[u][1] + (subtree[0][1] - subtree[u][1])
    ) % mod;
  }

  for (Edge &e: tree[u])
    if (e.v != prv)
      total = (total + dfs2(bit, ((e.w >> bit) & 1), e.v, u)) % mod;

  return total;
}

int main()
{
  while (~scanf("%d", &n))
  {
    for (int i = 1; i < n; i++)
    {
      Edge e; scanf("%d %d %lld", &e.u, &e.v, &e.w); e.u--, e.v--;
      tree[e.u].push_back(e);
      swap(e.u, e.v);
      tree[e.v].push_back(e);
    }

    lli ans = 0;
    for (int i = 0; i < 60; i++)
    {
      dfs(i);
      lli total = dfs2(i);
      
      if (i < 5)
        printf("\t%d - %lld\n", i, total);

      // ans = (ans + (1LL << i) * (b0 * a1 + a0 * b1) % mod) % mod;
      ans = (ans + (1LL << i) % mod * total % mod) % mod;
    }
    printf("%lld\n", ans);
  }
  return 0;
}