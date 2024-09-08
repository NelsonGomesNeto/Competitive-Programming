#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 16; int n;
vector<int> graph[1 << maxN];
int color[1 << maxN];
int cnt[maxN];

void dfs(int u = 0, int prv = -1)
{
  if (u == 0) color[u] = 0;

  int curr = color[u];
  for (int v: graph[u])
    if (color[v] == -1)
    {
      while (prv != -1 && curr == color[prv])
        curr = (curr + 1) % n;

      color[v] = curr;
      curr = (curr + 1) % n;
      dfs(v, u);
    }
}

int main()
{
  int t; scanf("%d", &t);
  for (int tt = 1; tt <= t; tt++)
  {
    scanf("%d", &n);
    for (int i = 0, end = n * (1 << (n - 1)); i < end; i++)
    {
      int u, v; scanf("%d %d", &u, &v);
      graph[u].push_back(v), graph[v].push_back(u);
    }

    memset(color, -1, sizeof(color));
    dfs();

    bool valid = true;
    for (int i = 0, end = 1 << n; i < end; i++)
    {
      memset(cnt, 0, sizeof(cnt));
      for (int v: graph[i])
        cnt[color[v]]++;
      for (int j = 0; j < n; j++)
        if (cnt[j] == 0)
          valid = false;
    }

    for (int i = 0, end = 1 << n; i < end; i++)
      printf("%d%c", i, i < end - 1 ? ' ' : '\n');
    if (!valid) printf("-1\n");
    else for (int i = 0, end = 1 << n; i < end; i++) printf("%d%c", color[i], i < end - 1 ? ' ' : '\n');
  }
  return 0;
}
