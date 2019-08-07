#include <bits/stdc++.h>
#define lli long long int
using namespace std;

const int maxN = 1e4; int n;
vector<int> graph[2][maxN];
int subtree[2][maxN], subtreeCount[2][maxN + 1];

int dfs(int kind, int u, int prv = -1)
{
  subtree[kind][u] = 1;
  for (int v: graph[kind][u])
    if (v != prv)
      subtree[kind][u] += dfs(kind, v, u);
  return(subtree[kind][u]);
}

void read(int kind)
{
  for (int i = 0; i < n; i ++) graph[kind][i].clear();
  for (int i = 0, u, v; i < n - 1; i ++)
  {
    scanf("%d %d", &u, &v); u --, v --;
    graph[kind][u].push_back(v), graph[kind][v].push_back(u);
  }
}

int main()
{
  while (scanf("%d", &n) != EOF)
  {
    read(0); read(1);
    bool same = false;
    for (int k = 0; k < n && !same; k ++)
    {
      if (graph[0][0].size() != graph[1][k].size()) continue;
      bool can = true;
      dfs(0, 0), dfs(1, k);
      for (int i = 0; i < n; i ++) subtreeCount[0][i] = subtreeCount[1][i] = 0;
      for (int i = 0; i < n; i ++)
        subtreeCount[0][subtree[0][i]] ++, subtreeCount[1][subtree[1][i]] ++;
      for (int i = 0; i < n && can; i ++)
        if (subtreeCount[0][i] != subtreeCount[1][i])
          can = false;
      same = can;
    }
    printf("%c\n", same ? 'S' : 'N');
  }
  return(0);
}