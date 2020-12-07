#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 2e5; int n, m;
int parents[maxN], sum[maxN], base[maxN];
char op[5];

int root(int u)
{
  if (parents[u] < 0)
    return u;

  int r = root(parents[u]);
  if (r != parents[u])
    sum[u] += sum[parents[u]], base[u] += base[parents[u]];

  return parents[u] = r;
}
void merge(int u, int v)
{
  u = root(u);
  v = root(v);
  if (u == v) return;
  if (parents[u] > parents[v]) swap(u, v);
  parents[u] += parents[v];
  parents[v] = u;

  base[v] += sum[u] - base[u];
}

int main()
{
  int tt = 0;
  while (scanf("%d %d", &n, &m) != EOF)
  {
    if (tt++) printf("\n");
    memset(parents, -1, sizeof(parents));
    memset(sum, 0, sizeof(sum));
    memset(base, 0, sizeof(base));

    for (int i = 0; i < m; i++)
    {
      scanf(" %s", op);
      if (!strcmp(op, "add"))
      {
        int u, v; scanf("%d %d", &u, &v); u--;
        sum[root(u)] += v;
      }
      else if (!strcmp(op, "join"))
      {
        int u, v; scanf("%d %d", &u, &v); u--, v--;
        merge(u, v);
      }
      else
      {
        int u; scanf("%d", &u); u--;
        int r = root(u);
        int ans = sum[r] - base[r] + (sum[u] - base[u]) * (u != r);
        DEBUG printf("get %d | root %d | value %d | %d %d %d\n", u + 1, r + 1, ans, sum[r], base[u], sum[u]);
        else printf("%d\n", ans);
      }
    }
  }
  return 0;
}