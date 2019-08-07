#include <bits/stdc++.h>
#define DEBUG if(0)
using namespace std;

const int maxN = 500, inf = 1e9; int n, m, q;
int age[maxN], id[maxN], revID[maxN];
bool visited[maxN];
vector<int> graph[maxN];

int dfs(int u, bool first = true)
{
  DEBUG printf("\t%d(%d) %d\n", u + 1, id[u] + 1, first);
  if (visited[u]) return(inf);
  visited[u] = true;

  int ans = first ? inf : age[u];
  for (int v: graph[u])
    ans = min(ans, dfs(v, false));
  return(ans);
}

int main()
{
  while (scanf("%d %d %d", &n, &m, &q) != EOF)
  {
    DEBUG printf("--------------\n");
    for (int i = 0; i < n; i ++) scanf("%d", &age[i]), id[i] = i, graph[i].clear();
    for (int i = 0, u, v; i < m; i ++)
    {
      scanf("%d %d", &u, &v); u --, v --;
      graph[v].push_back(u);
    }
    while (q --)
    {
      char op; scanf(" %c", &op);
      if (op == 'P')
      {
        int u; scanf("%d", &u); u --;
        memset(visited, false, sizeof(visited));
        int ans = dfs(id[u]);
        if (ans == inf) printf("*\n");
        else printf("%d\n", ans);
      }
      else
      {
        int u, v; scanf("%d %d", &u, &v); u --, v --;
        swap(id[u], id[v]);
        swap(age[id[u]], age[id[v]]);
      }
    }
  }
  return(0);
}