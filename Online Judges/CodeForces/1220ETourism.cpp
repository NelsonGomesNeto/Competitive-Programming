#include <bits/stdc++.h>
#define lli long long int
using namespace std;

const int maxN = 2e5; int n, m, s;
list<int> graph[maxN];
int indegree[maxN];
lli w[maxN], pathSum[maxN];

int main()
{
  while (scanf("%d %d", &n, &m) != EOF)
  {
    memset(pathSum, 0, sizeof(pathSum)), memset(indegree, 0, sizeof(indegree));
    for (int i = 0; i < n; i ++) graph[i].clear();

    for (int i = 0; i < n; i ++)
      scanf("%lld", &w[i]);
    for (int i = 0; i < m; i ++)
    {
      int u, v; scanf("%d %d", &u, &v); u --, v --;
      graph[u].push_back(v), indegree[v] ++;
      graph[v].push_back(u), indegree[u] ++;
    }
    scanf("%d", &s); s --;

    queue<int> q;
    int bestLeaf = s;
    for (int i = 0; i < n; i ++)
      if (i != s && indegree[i] == 1)
        q.push(i);
    while (!q.empty())
    {
      int u = q.front(); q.pop();
      for (int v: graph[u])
      {
        if (v == s) continue;
        pathSum[u] = max(pathSum[u], pathSum[v]);
        if (-- indegree[v] == 1)
          q.push(v);
      }
      pathSum[u] += w[u];
      if (pathSum[u] > pathSum[bestLeaf])
        bestLeaf = u;
    }
    lli cyclesSum = 0;
    for (int i = 0; i < n; i ++)
      if (i == s || indegree[i] > 1)
        cyclesSum += w[i];

    printf("%lld\n", cyclesSum + pathSum[bestLeaf]);
  }
  return(0);
}
