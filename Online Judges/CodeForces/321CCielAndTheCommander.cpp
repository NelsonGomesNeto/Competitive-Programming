#include <bits/stdc++.h>
using namespace std;

const int maxN = 1e5;
vector<int> graph[maxN];
int dist[maxN], prv[maxN], commander[maxN], root;

void dfs(int u, int d)
{
  if (dist[u] != -1) return;
  dist[u] = d;
  for (int v: graph[u]) dfs(v, d + 1), prv[v] = u;
}

bool bfs()
{
  queue<pair<int, pair<int, int>>> q; q.push({root, {0, 0}});
  while (!q.empty())
  {
    int u = q.front().first, level = q.front().second.first, odd = q.front().second.second; q.pop();
    if (level && graph[u].size() > 2) odd = 1; 
    if (!odd && 'A' + level > 'Z') return(false);
    if (commander[u] != -1) continue;
    commander[u] = !odd ? 'A' + level : 'Z';
    for (int v: graph[u]) q.push({v, {level + odd, 1 - odd}});
  }
  return(true);
}

int main()
{
  int n; scanf("%d", &n);
  for (int i = 1, u, v; i < n; i ++)
  {
    scanf("%d %d", &u, &v); u --, v --;
    graph[u].push_back(v);
    graph[v].push_back(u);
  }

  // memset(dist, -1, sizeof(dist));
  // dfs(0, 0);
  // int biggestDistance = -1, mostDistant;
  // for (int i = 0; i < n; i ++)
  //   if (dist[i] > biggestDistance)
  //     biggestDistance = dist[i], mostDistant = i;
  // memset(dist, -1, sizeof(dist));
  // dfs(mostDistant, 0);
  // biggestDistance = -1;
  // for (int i = 0; i < n; i ++)
  //   if (dist[i] > biggestDistance)
  //     biggestDistance = dist[i], mostDistant = i;
  // int mid = (biggestDistance >> 1) + (biggestDistance & 1); root = mostDistant;
  // while (mid --) root = prv[root];

  bool can = false;
  for (root = 0; root < n; root ++)
  {
    memset(commander, -1, sizeof(commander));
    if (bfs()) { can = true; break; }
  }
  if (!can) printf("Impossible!\n");
  else for (int i = 0; i < n; i ++) printf("%c%c", commander[i], i < n - 1 ? ' ' : '\n');
  return(0);
}