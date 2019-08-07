#include <bits/stdc++.h>
#define lli long long int
using namespace std;

const int maxMen = 1e6, maxWomen = 1e6; int men, women;

// all women will be from maxMen to (maxMen + maxWomen - 1)
lli groups[maxMen + maxWomen][2];
int parent[maxMen + maxWomen];
int root(int u)
{
  if (parent[u] < 0) return(u);
  return(parent[u] = root(parent[u]));
}
void merge(int u, int v)
{
  u = root(u), v = root(v);
  if (u == v) return;
  if (parent[v] < parent[u]) swap(u, v);
  parent[u] += parent[v];
  parent[v] = u;
}
int setSize(int u)
{
  return(-1 * parent[root(u)]);
}

int main()
{
  memset(parent, -1, sizeof(parent));
  scanf("%d %d", &men, &women);
  int q1; scanf("%d", &q1);
  for (int i = 0, u, v; i < q1; i ++)
  {
    scanf("%d %d", &u, &v); u --, v --;
    merge(u, v);
  }
  int q2; scanf("%d", &q2);
  for (int i = 0, u, v; i < q2; i ++)
  {
    scanf("%d %d", &u, &v); u --, v --;
    merge(men + u, men + v);
  }
  int q3; scanf("%d", &q3);
  for (int i = 0, u, v; i < q3; i ++)
  {
    scanf("%d %d", &u, &v); u --, v --;
    merge(u, v + men);
  }

  for (int i = 0, u, end = men + women; i < end; i ++)
  {
    u = root(i);
    groups[u][0] += i < men, groups[u][1] += i >= men;
  }

  lli ans = 0;
  for (int i = 0, end = men + women; i < end; i ++)
    ans += groups[i][0] * (women - groups[i][1]);
  printf("%lld\n", ans);

  return(0);
}