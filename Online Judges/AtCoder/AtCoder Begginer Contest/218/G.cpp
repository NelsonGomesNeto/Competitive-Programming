#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;

template <class T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 1e5; int n;
lli a[maxN];
vector<vector<int>> t;

ordered_set<pair<lli, int>> os;
lli dfs(int u = 0, int prv = -1, int turn = 0)
{
  auto now = make_pair(a[u], u);
  os.insert(now);

  if (t[u].size() == 1 && t[u][0] == prv)
  {
    int sz = os.size();
    lli ans = os.find_by_order(sz >> 1)->first;
    if (~sz & 1) ans = (ans + os.find_by_order((sz - 1) >> 1)->first) >> 1;
    os.erase(now);
    return ans;
  }

  lli best = turn ? 1e18 : -1e18;

  for (int v: t[u])
    if (v != prv)
    {
      lli curr = dfs(v, u, !turn);
      if (turn) best = min(best, curr);
      else best = max(best, curr);
    }

  os.erase(now);
  return best;
}

int main()
{
  while (~scanf("%d", &n))
  {
    for (int i = 0; i < n; i++)
      scanf("%lld", &a[i]);

    t.clear();
    t.resize(n);
    for (int i = 1; i < n; i++)
    {
      int u, v; scanf("%d %d", &u, &v); u--, v--;
      t[u].push_back(v), t[v].push_back(u);
    }

    lli ans = dfs();
    printf("%lld\n", ans);
  }
  return 0;
}