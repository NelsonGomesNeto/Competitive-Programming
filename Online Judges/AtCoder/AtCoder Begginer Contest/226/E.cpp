#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 2e5; int n, m;
const lli mod = 998244353;
vector<int> graph[maxN];
int indegree[maxN];
bool done[maxN];

void paint(int u, set<int> &curr)
{
  curr.insert(u);
  done[u] = true;
  for (int v: graph[u])
    if (!done[v])
      paint(v, curr);
}

int main()
{
  while (~scanf("%d %d", &n, &m))
  {
    for (int i = 0; i < n; i++) graph[i].clear(), indegree[i] = 0, done[i] = false;
    for (int i = 0; i < m; i++)
    {
      int u, v; scanf("%d %d", &u, &v); u--, v--;
      indegree[u]++, indegree[v]++;
      graph[u].push_back(v), graph[v].push_back(u);
    }
    bool can = true;

    queue<int> q;
    for (int i = 0; i < n; i++)
    {
      if (indegree[i] == 1 && indegree[graph[i][0]] > 1)
        q.push(i);
      if (indegree[i] == 0)
        can = false;
    }

    if (!can) printf("0\n");
    else
    {
      while (!q.empty())
      {
        int u = q.front(); q.pop();
        done[u] = true;
        for (int v: graph[u])
          if (--indegree[v] == 1 && indegree[graph[v][0]] > 1)
            q.push(v);
      }

      DEBUG {
        for (int i = 0; i < n; i++)
          printf("\t%d - %d\n", i + 1, done[i]);
      }

      lli ans = 1;
      for (int i = 0; i < n; i++)
        if (!done[i])
        {
          set<int> now;
          paint(i, now);
          int edgeCount = 0;
          for (int u: now)
            for (int v: graph[u])
              if (now.count(v))
                edgeCount++;
          DEBUG printf("\t\t%d %d %d\n", i, (int)now.size(), edgeCount);
          if (edgeCount != 2*now.size())
            can = false;

          ans = ans * 2 % mod;
        }
      if (!can) printf("0\n");
      else printf("%lld\n", ans);
    }
  }
  return 0;
}