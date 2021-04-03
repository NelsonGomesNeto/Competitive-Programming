#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 2e5; int n, q;
vector<int> tree[maxN];
lli up[maxN], down[maxN];
lli ans[maxN];
pair<int, int> edges[maxN];

int level[maxN];
vector<int> leafs;
void precalc(int u = 0, int prv = -1)
{
  bool hasChild = false;
  for (int v: tree[u])
    if (v != prv)
    {
      level[v] = level[u] + 1;
      precalc(v, u);
      hasChild = true;
    }
  if (!hasChild) leafs.push_back(u);
}

void pushDown(int u = 0, lli delta = 0)
{
  delta += down[u];

  ans[u] += delta;

  for (int v: tree[u])
    if (level[v] > level[u])
      pushDown(v, delta);
  
  // delta -= down[u];
}

int main()
{
  int tt = 0;
  while (~scanf("%d", &n))
  {
    if (tt++) printf("-------------\n");

    for (int i = 0; i < n; i++) tree[i].clear();
    memset(ans, 0, sizeof(ans));
    memset(up, 0, sizeof(up));
    memset(down, 0, sizeof(down));
    for (int i = 1; i < n; i++)
    {
      int u, v; scanf("%d %d", &u, &v); u--, v--;
      edges[i - 1].first = u, edges[i - 1].second = v;
      tree[u].push_back(v), tree[v].push_back(u);
    }

    leafs.clear();
    precalc();

    scanf("%d", &q);
    while (q--)
    {
      int t, e; lli x; scanf("%d %d %lld", &t, &e, &x); e--;
      int u = edges[e].first, v = edges[e].second;
      DEBUG printf("\t\t%d %d (%d, %d), %lld\n", t, e, u + 1, v + 1, x);

      if (t == 1)
      {
        if (level[u] > level[v]) down[u] += x;
        else up[u] += x, down[v] -= x;
      }
      else
      {
        if (level[v] > level[u]) down[v] += x;
        else up[v] += x, down[u] -= x;
      }
    }

    lli upTotal = 0;
    for (int i = 0; i < n; i++)
      upTotal += up[i];
    for (int i = 0; i < n; i++)
      ans[i] += upTotal;
    pushDown();

    for (int i = 0; i < n; i++)
      printf("%lld\n", ans[i]);
  }
  return 0;
}