#include <bits/stdc++.h>
#define lli long long int
using namespace std;

const int maxN = 1e3; int n;
int matchId[maxN][maxN], a[maxN][maxN], t, indegree[maxN*maxN];
vector<int> graph[maxN*maxN];

int main()
{
  memset(matchId, -1, sizeof(matchId));
  scanf("%d", &n);
  for (int u = 0; u < n; u ++)
    for (int i = 0; i < n - 1; i ++)
    {
      int v; scanf("%d", &v); v --;
      a[u][i] = v;
      if (matchId[min(u, v)][max(u, v)] == -1)
        matchId[min(u, v)][max(u, v)] = t ++;
    }

  for (int u = 0; u < n; u ++)
    for (int i = 1; i < n - 1; i ++)
    {
      graph[matchId[min(u, a[u][i - 1])][max(u, a[u][i - 1])]].push_back(matchId[min(u, a[u][i])][max(u, a[u][i])]);
      indegree[matchId[min(u, a[u][i])][max(u, a[u][i])]] ++;
    }

  int ans = 0;
  queue<pair<int, int>> q;
  for (int i = 0; i < t; i ++)
    if (indegree[i] == 0)
      q.push({i, 1});
  int matches = t;
  while (!q.empty())
  {
    int u = q.front().first, d = q.front().second; q.pop();
    ans = max(ans, d); matches --;
    // printf("%d %d | %d\n", u, d, matches);
    for (int v: graph[u])
    {
      // printf("\t%d\n", v);
      if (-- indegree[v] == 0)
        q.push({v, d + 1});
    }
  }
  printf("%d\n", !matches ? ans : -1);

  return(0);
}