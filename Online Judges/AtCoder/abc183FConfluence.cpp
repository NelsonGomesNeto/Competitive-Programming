#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 2e5; int n, q;
int parents[maxN];
map<int, int> cnt[maxN];
int root(int u)
{
  return parents[u] < 0 ? u : parents[u] = root(parents[u]);
}
void merge(int u, int v)
{
  u = root(u), v = root(v);
  if (u == v) return;
  if (parents[u] > parents[v]) swap(u, v);
  parents[u] += parents[v];
  parents[v] = u;
  for (auto &i: cnt[v])
  {
    if (!cnt[u].count(i.first))
      cnt[u][i.first] = 0;
    cnt[u][i.first] += i.second;
  }
}

int main()
{
  while (scanf("%d %d", &n, &q) != EOF)
  {
    memset(parents, -1, sizeof(parents));
    for (int i = 0; i < n; i++)
    {
      int c; scanf("%d", &c);
      cnt[i].clear();
      cnt[i][c] = 1;
    }

    while (q--)
    {
      int op; scanf("%d", &op);
      if (op == 1)
      {
        int u, v; scanf("%d %d", &u, &v); u--, v--;
        merge(u, v);
      }
      else
      {
        int u, c; scanf("%d %d", &u, &c); u--;
        u = root(u);
        if (!cnt[u].count(c)) printf("0\n");
        else printf("%d\n", cnt[u][c]);
      }
    }
  }
  return 0;
}