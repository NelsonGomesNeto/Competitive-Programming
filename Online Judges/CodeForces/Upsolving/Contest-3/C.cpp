#include <bits/stdc++.h>
#define DEBUG if(1)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 1e5; int n;
vector<int> tree[maxN];
map<pair<int, int>, int> edges;
int ans[maxN];

list<int> order;
void dfs(int u = 0, int prv = -1, bool turn = false)
{
  if (prv != -1)
  {
    if (turn) order.push_back(edges[{u, prv}]);
    else order.push_front(edges[{u, prv}]);
  }
  for (int v: tree[u])
    if (v != prv)
      dfs(v, u, !turn);
}

int main()
{
  while (scanf("%d", &n) != EOF)
  {
    memset(ans, -1, sizeof(ans));
    edges.clear(), order.clear();
    for (int i = 0; i < n; i ++)
      tree[i].clear();

    for (int i = 1; i < n; i ++)
    {
      int u, v; scanf("%d %d", &u, &v); u --, v --;
      tree[u].push_back(v), tree[v].push_back(u);
      edges[{u, v}] = edges[{v, u}] = i - 1;
    }

    dfs();
    int i = 0;
    for (int o: order)
      ans[o] = i ++;

    for (int i = 0; i < n - 1; i ++)
      printf("%d\n", ans[i]);
  }
  return 0;
}
