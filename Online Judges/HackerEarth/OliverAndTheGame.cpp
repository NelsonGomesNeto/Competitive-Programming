#include <bits/stdc++.h>
using namespace std;

const int maxN = 1e5;
vector<int> graph[maxN];

int in[maxN], out[maxN], t = 0;
void dfs(int u, int prv)
{
  in[u] = ++ t;
  for (int v: graph[u])
    if (v != prv)
      dfs(v, u);
  out[u] = ++ t;
}

int main()
{
  int n; scanf("%d", &n);
  for (int i = 0, u, v; i < n - 1; i ++)
  {
    scanf("%d %d", &u, &v); u --, v --;
    graph[u].push_back(v); graph[v].push_back(u);
  }

  dfs(0, -1);

  int q; scanf("%d", &q);
  while (q --)
  {
    int op, u, v; scanf("%d %d %d", &op, &u, &v); u --, v --;
    printf("%s\n", (!op ? (in[v] <= out[u] && in[u] <= in[v]) : (in[u] <= out[v] && in[v] <= in[u])) ? "YES" : "NO");
  }
  return(0);
}