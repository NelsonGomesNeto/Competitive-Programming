#include <bits/stdc++.h>
#define lli long long int
using namespace std;

const int maxV = 1 + 40 + 40 + 1, maxN = 40, inf = 1e9; int n, m, g;
int scores[maxN], games[maxN], playedWith[maxN][maxN];

// source (0) -[2*leftGames]> teams (1 : n) -[2*gamesInCommon]> teams (1 + n : 1 + n + n - 1) -[restrict maximum score]> target (1 + n + n)
//                                              ^ also add edge to your self with 2*leftGames
int source = 0, target, vertices;
struct Edge { int to, back, flow, capacity; };
vector<Edge> graph[maxV];
void addEdge(int u, int v, int f)
{
  graph[u].push_back({v, (int) graph[v].size(), f, f});
  graph[v].push_back({u, (int) graph[u].size() - 1, 0, 0});
}
int ptr[maxV], level[maxV];
bool bfs()
{
  memset(level, -1, sizeof(level)); level[source] = 0;
  queue<int> q; q.push(source);
  while (!q.empty())
  {
    int u = q.front(); q.pop();
    for (auto &e: graph[u])
      if (level[e.to] == -1 && e.flow)
        q.push(e.to), level[e.to] = level[u] + 1;
  }
  return(level[target] != -1);
}
int dfs(int u = source, int flow = inf)
{
  if (u == target || !flow) return(flow);
  for (int &p = ptr[u]; p < graph[u].size(); p ++)
  {
    auto &e = graph[u][p];
    if (level[e.to] == level[u] + 1 && e.flow)
    {
      int delivered = dfs(e.to, min(e.flow, flow));
      e.flow -= delivered;
      graph[e.to][e.back].flow += delivered;
      if (delivered) return(delivered);
    }
  }
  return(0);
}
int dinic()
{
  int maxFlow = 0, flow;
  while (bfs())
  {
    memset(ptr, 0, sizeof(ptr));
    while (flow = dfs()) maxFlow += flow;
  }
  return(maxFlow);
}

int main()
{
  while (scanf("%d %d %d", &n, &m, &g) != EOF && !(n == 0 && m == 0 && g == 0))
  {
    memset(games, 0, sizeof(games)), memset(scores, 0, sizeof(scores)), memset(playedWith, 0, sizeof(playedWith));
    target = 1 + n + n; vertices = target + 1;
    for (int i = 0; i < vertices; i ++) graph[i].clear();

    for (int i = 0; i < g; i ++)
    {
      int u, v; char d;
      scanf("%d %c %d", &u, &d, &v);
      games[u] ++, scores[u] += d == '>' ? 2 : d == '=' ? 1 : 0,
      games[v] ++, scores[v] += d == '<' ? 2 : d == '=' ? 1 : 0;
      playedWith[u][v] ++, playedWith[v][u] ++;
    }
    for (int i = 1; i < n; i ++)
      if (playedWith[0][i] < m)
      {
        int toPlay = m - playedWith[0][i];
        games[0] += toPlay, scores[0] += 2 * toPlay, games[i] += toPlay, g += toPlay;
        playedWith[0][i] += toPlay, playedWith[i][0] += toPlay;
      }

    bool can = true;
    for (int i = 1; i < n; i ++)
      if (scores[i] >= scores[0])
        can = false;
    if (can)
    {
      int required = n * m * (n - 1) - 2 * g, req = 0;
      for (int i = 1; i < n; i ++)
      {
        int missing = 0;
        for (int j = i + 1; j < n; j ++)
          if (playedWith[i][j] < m)
            addEdge(1 + i, 1 + n + j, 2 * (m - playedWith[i][j])), missing += 2 * (m - playedWith[i][j]);
        addEdge(1 + i, 1 + n + i, missing);
        addEdge(source, 1 + i, missing);
      }
      for (int i = 1; i < n; i ++)
        addEdge(1 + n + i, target, scores[0] - scores[i] - 1);

      int ans = dinic();
      if (ans < required) can = false;
    }
    printf("%c\n", can ? 'Y' : 'N');
  }
  return(0);
}