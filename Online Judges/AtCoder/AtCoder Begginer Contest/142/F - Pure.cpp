#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 1e3; int n, m;
vector<int> graph[maxN];
bool reachable[maxN][maxN];
bool anyReachable[maxN][maxN];

void reach(int origin, int u)
{
  reachable[origin][u] = true;

  for (int v: graph[u])
    reachable[origin][v] = true;
    // if (!reachable[origin].count(v))
    //   reach(origin, v);
}
void anyReach(int origin, int u)
{
  anyReachable[origin][u] = true;

  for (int v: graph[u])
    if (!anyReachable[origin][v])
      anyReach(origin, v);
}

int level[maxN];
void fillLevels(int origin)
{
  memset(level, -1, sizeof(level));
  queue<int> q; q.push(origin);
  level[origin] = 0;
  while (!q.empty())
  {
    int u = q.front(); q.pop();
    for (int v: graph[u])
      if (level[v] == -1)
        level[v] = level[u] + 1, q.push(v);
  }
}

int forbidden[maxN];
list<int> ans;
bool has[maxN];
bool dfs(int origin, int u, int depth = 0)
{
  if (level[u] != depth)
    return false;

  for (int v: graph[u])
    if (has[v] && v != origin)
      return false;

  for (int v: graph[u])
    if (v == origin)
    {
      ans.push_back(u), has[u] = true;
      return true;
    }

  ans.push_back(u), has[u] = true;
  list<int> unforbid;
  for (int v: graph[u])
    if (forbidden[v] == -1)
      forbidden[v] = u, unforbid.push_back(v);
  auto it = prev(ans.end());
  for (int v: graph[u])
  {
    if (!anyReachable[v][origin])
      continue;

    bool allowed = forbidden[v] == -1 || forbidden[v] == u;

    if (allowed && dfs(origin, v, depth + 1))
      return true;
  }
  ans.erase(it), has[u] = false;
  for (int v: unforbid)
    forbidden[v] = -1;

  return false;
}

int main()
{
  int t = 0;
  while (~scanf("%d %d", &n, &m))
  {
    if (t++)
    {
      memset(reachable, false, sizeof(reachable));
      memset(anyReachable, false, sizeof(anyReachable));
    }
    for (int i = 0; i < n; i++)
      graph[i].clear();

    for (int i = 0; i < m; i++)
    {
      int u, v; scanf("%d %d", &u, &v); u--, v--;
      graph[u].push_back(v);
    }

    for (int u = 0; u < n; u++)
    {
      reach(u, u);
      anyReach(u, u);
      DEBUG {
        printf("reachable(%d):", u + 1);
        for (int v: reachable[u]) printf(" %d", v + 1);
        printf("\n");
      }
    }

    bool can = false;
    for (int u = 0; u < n && !can; u++)
    {
      ans.clear();
      memset(has, false, sizeof(has));
      memset(forbidden, -1, sizeof(forbidden));
      fillLevels(u);
      if (dfs(u, u))
      {
        can = true;
        break;
      }
    }
    DEBUG printf("%s\n", can ? "Yes" : "No");

    if (!can) printf("-1\n");
    else
    {
      printf("%d\n", (int)ans.size());
      for (int u: ans) printf("%d\n", u + 1);
    }
  }
  return 0;
}