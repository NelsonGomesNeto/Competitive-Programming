#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 1e5; int n;
struct Edge
{
  int to, id;
};
vector<Edge> tree[maxN];
int colors[maxN];

void solve(int u = 0, int prv = -1, int prvColor = 0)
{
  int c = 0;
  for (Edge &e: tree[u])
    if (e.to != prv)
    {
      c ++;
      if (prvColor == c) c ++;
      colors[e.id] = c;
      solve(e.to, u, c);
    }
}

int main()
{
  while (scanf("%d", &n) != EOF)
  {
    for (int i = 0; i < n; i ++)
      tree[i].clear();
    for (int i = 0; i < n - 1; i ++)
    {
      int u, v; scanf("%d %d", &u, &v); u --, v --;
      tree[u].push_back({v, i}), tree[v].push_back({u, i});
    }

    solve();
    int k = 1;
    for (int i = 0; i < n - 1; i ++)
      k = max(k, colors[i]);
    printf("%d\n", k);
    for (int i = 0; i < n - 1; i ++)
      printf("%d%c", colors[i], i < n - 2 ? ' ' : '\n');
  }
  return 0;
}