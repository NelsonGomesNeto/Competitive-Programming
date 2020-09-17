#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 1e5; int n, a, b, da, db;
vector<int> tree[maxN];

bool updatedAlicePos;
int dist[maxN];
bool dfsAlice(bool toUpdate, int u = a, int prv = -1, int d = 0)
{
  bool found = false;
  dist[u] = d;
  if (u == b)
  {
    if (d <= da && toUpdate) a = u, updatedAlicePos = true;
    found = true;
  }

  for (int v: tree[u])
    if (v != prv && dfsAlice(toUpdate, v, u, d + 1))
    {
      if (!updatedAlicePos && d <= da && toUpdate)
        a = u, updatedAlicePos = true;
      found = true;
    }
  return found;
}

int bestBobDist = 0;
void dfsBob(int u = b, int prv = -1, int d = 0)
{
  if (d <= db && dist[u] > bestBobDist)
    bestBobDist = dist[u], b = u;

  for (int v: tree[u])
    if (v != prv)
      dfsBob(v, u, d + 1);
}

int prv[maxN];
int bfs(int u)
{
  memset(dist, -1, sizeof(dist));
  queue<int> q; q.push(u); dist[u] = 1;
  while (!q.empty())
  {
    int u = q.front(); q.pop();
    for (int v: tree[u])
      if (dist[v] == -1)
        dist[v] = dist[u] + 1, prv[v] = u, q.push(v);
  }
  return max_element(dist, dist+n) - dist;
}

int main()
{
  int t;
  while (scanf("%d", &t) != EOF)
    for (int tt = 1; tt <= t; tt++)
    {
      scanf("%d %d %d %d %d", &n, &a, &b, &da, &db); a--, b--;
      for (int i = 0; i < n; i++) tree[i].clear();
      for (int i = 1; i < n; i++)
      {
        int u, v; scanf("%d %d", &u, &v); u--, v--;
        tree[u].push_back(v), tree[v].push_back(u);
      }

      int mostDistant = bfs(0);
      int secondMostDistant = bfs(mostDistant);
      int diameter = dist[secondMostDistant];
      bool can = (diameter >> 1) <= da || db <= 2*da ? true : false;

      // bool can = false;
      for (int turns = 0; turns < 2; turns++)
      {
        if (turns & 1) // bob
        {
          dfsAlice(false);
          bestBobDist = 0;
          dfsBob();
        }
        else // alice
        {
          updatedAlicePos = false;
          dfsAlice(true);
          if (a == b)
            can = true;
        }
      }
      printf("%s\n", can ? "Alice" : "Bob");
    }
  return 0;
}