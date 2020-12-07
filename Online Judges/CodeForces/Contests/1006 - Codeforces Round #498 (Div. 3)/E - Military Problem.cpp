#include <bits/stdc++.h>
#define DEBUG if(0)
using namespace std;
int n, q, at;

void dfs(vector<int> graph[], int u, int order[], pair<int, int> inout[])
{
  inout[u].first = at;
  order[at ++] = u + 1;
  for (auto v: graph[u]) dfs(graph, v, order, inout);
  inout[u].second = at - 1;
}

int main()
{
  scanf("%d %d", &n, &q);
  vector<int> graph[n], rev[n];
  for (int i = 0, u; i < n - 1; i ++)
  {
    scanf("%d", &u);
    graph[u - 1].push_back(i + 1);
    rev[i + 1].push_back(u - 1);
  }
  at = 0; int order[n]; pair<int, int> inout[n];
  dfs(graph, 0, order, inout);
  DEBUG for (int i = 0; i < n; i ++) printf("%d%c", order[i], i < n - 1 ? ' ' : '\n');

  while (q --)
  {
    int u, k; scanf("%d %d", &u, &k); u --; k --;
    if (k > inout[u].second - inout[u].first) printf("-1\n");
    else printf("%d\n", order[k + inout[u].first]);
  }
  return(0);
}