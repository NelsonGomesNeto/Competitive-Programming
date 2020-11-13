#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxV = 1e5; int n, m, q;
vector<int> graph[maxV];
int visited[maxV];
int bfs(int origin, int target)
{
  queue<pair<int, set<int>>> q;
  q.push({origin, {origin}});
  set<int> res;

  while (!q.empty())
  {
    auto now = q.front(); q.pop();
    int u = now.first;
    if (u == target)
    {
      if (res.empty()) res = now.second;
      else
      {
        list<int> toRem;
        for (int i: res) if (!now.second.count(i)) toRem.push_back(i);
        for (int i: toRem) res.erase(i);
      }
    }
    for (int v: graph[u])
      if (!now.second.count(v))
      {
        set<int> aux = now.second;
        aux.insert(v);
        q.push({v, aux});
      }
  }

  return res.size();
}

set<int> res, curr;
void dfs(int u, int target)
{
  if (u == target)
  {
    if (res.empty()) res = curr;
    else
    {
      list<int> toRem;
      for (int i: res) if (!curr.count(i)) toRem.push_back(i);
      for (int i: toRem) res.erase(i);
    }
    return;
  }
  for (int v: graph[u])
    if (!curr.count(v))
    {
      curr.insert(v);
      dfs(v, target);
      curr.erase(v);
    }
}

int main()
{
  while (scanf("%d %d", &n, &m) != EOF)
  {
    for (int i = 0; i < m; i++)
    {
      int u, v; scanf("%d %d", &u, &v); u--, v--;
      graph[u].push_back(v), graph[v].push_back(u);
    }

    int q; scanf("%d", &q);
    while (q--)
    {
      int u, v; scanf("%d %d", &u, &v); u--, v--;
      curr.clear(), res.clear();
      curr.insert(u);
      dfs(u, v);
      printf("%d\n", (int)res.size());
    }
  }
  return 0;
}