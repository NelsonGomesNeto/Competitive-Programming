#include <bits/stdc++.h>
using namespace std;

/* Explanation:
victories = n
for each person p:
  let p be the wolf
  every person that can kill p, will kill p | let's say he has wolfVotes
  the remaining ones must vote optimally, such that
  every other person has at most wolfVotes - 1
  run a maxFlow algorithm
    where the capacity is (wolfVotes - 2 if the wolf can kill that person else wolfVotes - 1)
  if the flow is equal to the amount of voters (not considering the ones that killed the wolf)
  victories -= 1
*/

// source (0) -> people (1 : 50) -> people (51 : 100) -> target (101)
const int maxN = 50, maxVertices = 102; int source, target, vertices;
struct Edge { int to, back, flow, capacity; };
vector<Edge> graph[maxVertices];
void clearGraph()
{
  for (int i = 0; i < vertices; i ++) graph[i].clear();
}
void addEdge(int u, int v, int f)
{
  graph[u].push_back({v, (int) graph[v].size(), f, f});
  graph[v].push_back({u, (int) graph[u].size() - 1, 0, 0});
}

const int inf = 1e9;
int level[maxVertices], ptr[maxVertices];
bool bfs()
{
  memset(level, -1, sizeof(level));
  queue<int> q; q.push(source), level[source] = 0;
  while (!q.empty())
  {
    int u = q.front(); q.pop();
    for (Edge &e: graph[u])
      if (level[e.to] == -1 && e.flow > 0)
        q.push(e.to), level[e.to] = level[u] + 1;
  }
  return(level[target] != -1);
}
int dfs(int u, int flow)
{
  if (u == target || !flow) return(flow);
  for (int &p = ptr[u]; p < graph[u].size(); p ++)
  {
    Edge &e = graph[u][p];
    if (level[e.to] == level[u] + 1 && e.flow > 0)
    {
      int delivered = dfs(e.to, min(flow, e.flow));
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
    while (flow = dfs(source, inf)) maxFlow += flow;
  }
  return(maxFlow);
}

int main()
{
  int n; scanf("%d", &n); vertices = 2*n + 2; target = vertices - 1;
  bool planToKill[n][n]; memset(planToKill, false, sizeof(planToKill));
  int plan[n][2];
  for (int i = 0, a, b; i < n; i ++)
  {
    scanf("%d %d", &a, &b); a --, b --;
    planToKill[i][a] = planToKill[i][b] = true, plan[i][0] = a, plan[i][1] = b;
  }

  int wins = n;
  for (int i = 0; i < n; i ++)
  {
    int wolfVotes = 0, voters = n - 1; bool voted[n]; memset(voted, false, sizeof(voted)); voted[i] = true;
    for (int j = 0; j < n; j ++) if (planToKill[j][i]) wolfVotes ++, voted[j] = true, voters --;
    clearGraph();
    for (int j = 0; j < n; j ++) if (!voted[j]) addEdge(source, 1 + j, 1);
    for (int j = 0; j < n; j ++)
      if (!voted[j])
        addEdge(1 + j, 1 + n + plan[j][0], 1), addEdge(1 + j, 1 + n + plan[j][1], 1);
    for (int j = 0; j < n; j ++) addEdge(1 + n + j, target, max(0, wolfVotes - (planToKill[i][j] ? 2 : 1)));
    int flow = dinic();
    if (flow == voters) wins --;
  }
  printf("%d\n", wins);

  return(0);
}