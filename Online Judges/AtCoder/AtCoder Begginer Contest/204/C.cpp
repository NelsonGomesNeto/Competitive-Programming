#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 2e3; int n, m;
vector<int> graph[maxN];
bool ways[maxN][maxN], visited[maxN];

int main()
{
  while (~scanf("%d %d", &n, &m))
  {
    memset(ways, false, sizeof(ways));
    for (int i = 0; i < n; i++) graph[i].clear();

    for (int i = 0; i < m; i++)
    {
      int u, v; scanf("%d %d", &u, &v); u--, v--;
      graph[u].push_back(v);
    }

    int ans = 0;
    for (int i = 0; i < n; i++)
    {
      queue<int> q; q.push(i);
      memset(visited, false, sizeof(visited));
      while (!q.empty())
      {
        int u = q.front(); q.pop();
        if (visited[u]) continue;
        visited[u] = true;
        ans += !ways[i][u];
        ways[i][u] = true;
        for (int v: graph[u])
          q.push(v);
      }
    }
    printf("%d\n", ans);
  }
  return 0;
}