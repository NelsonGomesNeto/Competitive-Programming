#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxV = 1e5; int n, m, q;
vector<int> graph[maxV];
int visited[maxV], prv[maxV];
// mark the path (prv)
// check if 
int bfs(int origin, int target, bool reversed = false)
{
  queue<pair<int, int>> q;
  q.push({origin, -1});

  while (!q.empty())
  {
    auto now = q.front(); q.pop();
    int u = now.first, p = now.second;
    if (u == target) break;
    if (visited[u]) continue;
    visited[u] = true;
    prv[u] = p;

    if (reversed)
    {
      for (int i = graph[u].size() - 1; i >= 0; i--)
      {
        int v = graph[u][i];
        q.push({v, u});
      }
    }
    else
      for (int v: graph[u])
        q.push({v, u});
  }
  return 0;
}

void dfs(int u, int target)
{
  if (visited[u])
  {
    prv[u] = -1;
    return;
  }
  visited[u] = true;
  for (int v: graph[u])
    dfs(v, target);
}

int qans(int u, int v)
{
  set<int> a, b;
  fill(visited, visited+n, 0);
  fill(prv, prv+n, -1);
  bfs(u, v);
  fill(visited, visited+n, 0);
  for (int uu = v; uu != u && uu != -1; uu = prv[uu])
  {
    a.insert(uu);
    visited[uu] = true;
  }
  fill(prv, prv+n, -1);
  bfs(v, u, true);
  for (int uu = u; uu != v && uu != -1; uu = prv[uu])
    b.insert(uu);

  // for (int i: a)
  //   printf("%d ", i);
  // printf("\n");

  // for (int i: b)
  //   printf("%d ", i);
  // printf("\n");

  int ans = 2;
  for (int i: a)
    if (b.count(i))
      ans++;
  return ans;
  // bfs(u ,v);
  // fill(visited, visited+n, 0);
  // for (int uu = v; uu != u; uu = prv[uu])
  //   visited[uu] = true;
  // dfs(u, v);

  // int ans = 1;
  // for (int uu = v; uu != u && uu != -1; uu = prv[uu])
  //   ans++;
  // return ans;
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
      printf("%d\n", min(qans(u, v), qans(v, u)));
    }
  }
  return 0;
}