#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 1e5; int n, m;
vector<int> graph[maxN];

int parent[maxN];
void bfs()
{
  queue<pair<int, int>> q;
  q.push({0, -1});
  while (!q.empty())
  {
    int u = q.front().first, prv = q.front().second; q.pop();
    if (parent[u] != -1) continue;
    if (prv != -1) parent[u] = prv;
    for (int v: graph[u])
      q.push({v, u});
  }
}

int main()
{
  while (scanf("%d %d", &n, &m) != EOF)
  {
    for (int i = 0; i < n; i++) graph[i].clear();
    for (int i = 0; i < m; i++)
    {
      int u, v; scanf("%d %d", &u, &v); u--, v--;
      graph[u].push_back(v), graph[v].push_back(u);
    }

    memset(parent, -1, sizeof(parent));
    bfs();
    bool ans = true;
    for (int i = 1; i < n; i++)
      if (parent[i] == -1)
        ans = false;
    printf("%s\n", ans ? "Yes" : "No");
    if (ans)
      for (int i = 1; i < n; i++)
        printf("%d\n", parent[i] + 1);
  }
  return 0;
}