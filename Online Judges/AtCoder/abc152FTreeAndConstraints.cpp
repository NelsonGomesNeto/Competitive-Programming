#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 50, maxM = 20; int n, m;
int edgesSolves[maxN];
vector<pair<int, int>> tree[maxN];
vector<pair<int, int>> restrictions;

bool fillEdgesSolves(int u, int target, int r, int prv = -1)
{
  if (u == target) return true;
  for (auto &e: tree[u])
    if (e.first != prv && fillEdgesSolves(e.first, target, r, u))
    {
      edgesSolves[e.second] |= 1 << r;
      return true;
    }
  return false;
}

lli memo[maxN][1 << maxM];
lli solve(int i = 0, int bitmask = 0)
{
  if (i == n - 1) return bitmask == ((1 << restrictions.size()) - 1);
  if (memo[i][bitmask] != -1) return memo[i][bitmask];
  return memo[i][bitmask] = solve(i + 1, bitmask) + solve(i + 1, bitmask | edgesSolves[i]);
}

int main()
{
  while (scanf("%d", &n) != EOF)
  {
    for (int i = 0; i < n; i ++) tree[i].clear();
    memset(edgesSolves, 0, sizeof(edgesSolves));
    restrictions.clear();

    for (int i = 0; i < n - 1; i ++)
    {
      int u, v; scanf("%d %d", &u, &v); u --, v --;
      tree[u].push_back({v, i}), tree[v].push_back({u, i});
    }
    scanf("%d", &m);
    for (int i = 0; i < m; i ++)
    {
      int u, v; scanf("%d %d", &u, &v); u --, v --;
      restrictions.push_back({u, v});
    }

    for (int i = 0; i < restrictions.size(); i ++)
    {
      auto &r = restrictions[i];
      fillEdgesSolves(r.first, r.second, i);
    }

    memset(memo, -1, sizeof(memo));
    lli ans = solve();
    printf("%lld\n", ans);
  }
  return 0;
}