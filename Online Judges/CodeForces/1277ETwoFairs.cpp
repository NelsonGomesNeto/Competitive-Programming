#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 2e5; int n, m, a, b;
set<int> ab[2];

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
lli setSize(int u)
{
  return -parent[root(u)];
}

int main()
{
  int t; scanf("%d", &t);
  while (t --)
  {
    scanf("%d %d %d %d", &n, &m, &a, &b); a --, b --;
    ab[0].clear(), ab[1].clear();
    for (int i = 0; i < n; i ++)
      parent[i] = -1;

    for (int i = 0; i < m; i ++)
    {
      int u, v; scanf("%d %d", &u, &v); u --, v --;
      if (u == a || u == b || v == a || v == b)
      {
        if (u == a) ab[0].insert(v);
        if (v == a) ab[0].insert(u);
        if (u == b) ab[1].insert(v);
        if (v == b) ab[1].insert(u);
        continue;
      }
      merge(u, v);
    }
    ab[0].erase(a), ab[0].erase(b);
    ab[1].erase(a), ab[1].erase(b);
    set<int> aSide, bSide, both;

    for (int u: ab[0])
      aSide.insert(root(u));
    for (int u: ab[1])
      bSide.insert(root(u));
    for (int u: aSide)
      if (bSide.count(u))
        both.insert(u);
    for (int u: both)
      aSide.erase(u), bSide.erase(u);

    DEBUG {
      printf("\t%d %d\n", a, b);
      for (int i = 0; i < n; i ++)
        printf("%d%c", root(i), i < n - 1 ? ' ' : '\n');
      for (int u: aSide)
        printf("%d ", u);
      printf("\n");
      for (int u: bSide)
        printf("%d ", u);
      printf("\n");
    }

    lli aSize = 0, bSize = 0;
    for (int u: aSide)
      aSize += setSize(u);
    for (int u: bSide)
      bSize += setSize(u);
    lli ans = aSize * bSize;
    printf("%lld\n", ans);
  }
  return 0;
}
