#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 1e5; int n, m;
int color[maxN];
vector<int> graph[maxN];

bool visited[maxN];
void dfs(int u = 0)
{
  if (visited[u]) return;
  visited[u] = true;
  for (int v: graph[u])
    dfs(v);
}

int main()
{
  scanf("%d %d", &n, &m);
  for (int i = 0; i < m; i ++)
  {
    int u, v; scanf("%d %d", &u, &v); u --, v --;
    graph[u].push_back(v), graph[v].push_back(u);
  }
  memset(color, -1, sizeof(color));
  for (int i = 0; i < n; i ++)
    if (color[i] == -1)
    {
      color[i] = 0;
      for (int j: graph[i])
        color[j] = 1;
    }

  for (int i = 0; i < n; i ++)
    if (color[i] == 1)
      for (int j: graph[i])
        if (color[j] == 1)
          color[j] = 2;

  bool valid = true;
  dfs();
  for (int i = 0; i < n; i ++) if (!visited[i]) valid = false;
  int cnt[3] = {0, 0, 0};
  for (int i = 0; i < n; i ++)
  {
    if (color[i] == -1) valid = false;
    else cnt[color[i]] ++;
  }
  valid = valid && cnt[0] && cnt[1] && cnt[2];
  if (valid)
    for (int i = 0; i < n; i ++)
      if (graph[i].size() != n - cnt[color[i]])
        valid = false;
  if (!valid) printf("-1\n");
  else for (int i = 0; i < n; i ++) printf("%d%c", color[i] + 1, i < n - 1 ? ' ' : '\n');

  return 0;
}