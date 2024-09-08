#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 1e3; int n, m;
vector<int> graph[maxN];
int indegree[maxN];


int main()
{
  while (scanf("%d %d", &n, &m) != EOF)
  {
    for (int i = 0; i < n; i++)
      graph[i].clear();
    memset(indegree, 0, sizeof(indegree));

    for (int i = 0; i < m; i++)
    {
      int u, v; scanf("%d %d", &u, &v); u--, v--;
      graph[u].push_back(v);
      indegree[v]++;
    }

    queue<int> q;
    for (int i = 0; i < n; i++)
    {
      if (indegree[i] == 0)
        q.push(i);
      if (isCycle(i, i))
      {
        indegree[i] = 0;
        q.push(i);
      }
    }

    vector<int> ans;
    while (!q.empty())
    {
      int u = q.front();
      DEBUG printf("\t%d | %d\n", u + 1, indegree[u]);
      ans.push_back(u);
      q.pop();

      for (int v: graph[u])
        if (indegree[v] && --indegree[v] == 0)
          q.push(v);

      for (int v: graph[u])
        if (indegree[v] && indegree[v] <= 2 && isCycle(v, v))
        {
          indegree[v] = 0;
          q.push(v);
        }
    }
    printf("%d\n", (int)ans.size());
  }
  return 0;
}