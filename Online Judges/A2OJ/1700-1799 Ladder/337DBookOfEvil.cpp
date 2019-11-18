#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 1e5; int n, m, d;
bool affected[maxN];
vector<int> graph[maxN];

int prv[maxN], dist[maxN];
int getMostDistant(int source)
{
  queue<pair<pair<int, int>, int>> q; q.push({{source, -1}, 0});
  int ans = source, dans = 0;
  while (!q.empty())
  {
    int u = q.front().first.first, uu = q.front().first.second, dis = q.front().second; q.pop();
    if (dis > dans && affected[u])
      dans = dis, ans = u;
    dist[u] = dis;
    for (int v: graph[u])
      if (v != uu)
        q.push({{v, u}, dis + 1}), prv[v] = u;
  }
  return ans;
}

int bfs(int source, int ignoreLeft, int ignoreRigth, int fuel)
{
  queue<pair<pair<int, int>, int>> q; q.push({{source, -1}, fuel});
  int ans = 0;
  while (!q.empty())
  {
    int u = q.front().first.first, uu = q.front().first.second, f = q.front().second; q.pop();
    if (f < 0) continue;
    ans ++;
    for (int v: graph[u])
      if (v != uu && v != ignoreLeft && v != ignoreRigth)
        q.push({{v, u}, f - 1});
  }
  return ans;
}

int main()
{
  while (scanf("%d %d %d", &n, &m, &d) != EOF)
  {
    for (int i = 0; i < n; i ++) graph[i].clear();
    memset(affected, false, sizeof(affected));
    for (int i = 0; i < m; i ++)
    {
      int p; scanf("%d", &p);
      affected[p - 1] = true;
    }

    for (int i = 0; i < n - 1; i ++)
    {
      int u, v; scanf("%d %d", &u, &v); u --, v --;
      graph[u].push_back(v), graph[v].push_back(u);
    }

    int aff = -1; for (int i = 0; i < n; i ++) if (affected[i]) aff = i;
    int secondMostDistant = getMostDistant(aff);
    int mostDistant = getMostDistant(secondMostDistant);
    vector<int> path;
    for (int i = mostDistant; i != secondMostDistant; i = prv[i])
      path.push_back(i);
    path.push_back(secondMostDistant);

    int ans = 0;
    for (int i = 0, lo = 0, hi = dist[mostDistant]; i < path.size(); i ++, lo ++, hi --)
      if (max(lo, hi) <= d)
        ans += bfs(path[i], i ? path[i - 1] : -1, i < path.size() - 1 ? path[i + 1] : -1, d - max(lo, hi));

    printf("%d\n", ans);
  }
  return 0;
}