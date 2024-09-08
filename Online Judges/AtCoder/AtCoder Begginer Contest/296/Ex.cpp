#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

template <typename T, typename G>
struct Edge
{
  int to, back;
  G flow;
  T cost;
};

template <typename T, typename G>
struct MinCostFlow
{
  int source, sink, vertices;
  G infFlow;
  T infCost;
  vector<int> prevVertex, prevEdge;
  vector<T> cost;
  vector<vector<Edge<T, G>>> graph;

  vector<bool> inqueue; // needed for SPFA

  vector<T> potentials;
  vector<bool> visited; // needed for Dijkstra with Potentials

  MinCostFlow() {}
  MinCostFlow(int vertices, int source, int sink, G infFlow = numeric_limits<G>::max(), T infCost = numeric_limits<T>::max())
      : vertices(vertices), source(source), sink(sink), infFlow(infFlow), infCost(infCost)
  {
    graph.resize(vertices, vector<Edge<T, G>>());
    prevVertex.resize(vertices), prevEdge.resize(vertices);
    cost.resize(vertices);

    inqueue.resize(vertices);

    potentials.resize(vertices), visited.resize(vertices);
  }
  void addEdge(int u, int v, G f, T c)
  {
    graph[u].push_back({v, (int)graph[v].size(), f, c});
    graph[v].push_back({u, (int)graph[u].size() - 1, 0, -c});
  }

  void printGraph()
  {
    printf("\ncost: %3d\n", cost[sink]);
    for (int v = sink, totalCost = 0; v != source; v = prevVertex[v])
    {
      totalCost += graph[prevVertex[v]][prevEdge[v]].cost;
      printf("%d%s", v, prevVertex[v] != source ? " <- " : " <- 0");
      if (prevVertex[v] == source)
        printf(" | totalCost: %d\n", totalCost);
    }
    for (int i = 0; i < vertices; i++)
    {
      printf("%2d (pot: %2d):", i, potentials[i]);
      int k = 0;
      for (auto &e : graph[i])
        printf(" (%2d, %2d, %3d)", e.to, e.flow, e.cost);
      printf("\n");
    }
  }

  bool bellmanFord() // slow
  {
    fill(cost.begin(), cost.end(), infCost);
    cost[source] = 0;
    for (int i = 0, done = 0; i < vertices - 1; i++, done = 0)
    {
      for (int u = 0; u < vertices; u++)
      {
        if (cost[u] == infCost)
          continue;
        int j = 0;
        for (const auto &e : graph[u])
        {
          T newCost = cost[u] + e.cost;
          if (e.flow && newCost < cost[e.to])
          {
            cost[e.to] = newCost;
            prevVertex[e.to] = u, prevEdge[e.to] = j;
            done = 1;
          }
          ++j;
        }
      }
      if (!done)
        break;
    }
    return cost[sink] != infCost;
  }
  bool dijkstraWithPotentials() // fast
  {
    fill(visited.begin(), visited.end(), false);
    fill(cost.begin(), cost.end(), infCost);
    priority_queue<pair<T, int>> pq;
    pq.push({0, source});
    cost[source] = 0;
    while (!pq.empty())
    {
      int u = pq.top().second;
      pq.pop();
      if (visited[u])
        continue;
      visited[u] = true;
      int j = 0;
      for (const auto &e : graph[u])
      {
        T newCost = cost[u] + e.cost + potentials[u] - potentials[e.to];
        if (e.flow && newCost < cost[e.to])
        {
          cost[e.to] = newCost;
          prevVertex[e.to] = u, prevEdge[e.to] = j;
          pq.push({-cost[e.to], e.to});
        }
        ++j;
      }
    }
    if (cost[sink] == infCost)
      return false;
    for (int i = 0; i < vertices; i++)
      potentials[i] += cost[i];
    return true;
  }
  bool SPFA() // fastest
  {
    fill(inqueue.begin(), inqueue.end(), false);
    fill(cost.begin(), cost.end(), infCost);
    queue<int> q;
    q.push(source);
    cost[source] = 0;
    while (!q.empty())
    {
      int u = q.front();
      q.pop();
      inqueue[u] = false;
      int j = 0;
      for (const auto &e : graph[u])
      {
        T newCost = cost[u] + e.cost;
        if (e.flow && newCost < cost[e.to])
        {
          if (!inqueue[e.to])
            inqueue[e.to] = true, q.push(e.to);
          cost[e.to] = newCost;
          prevVertex[e.to] = u, prevEdge[e.to] = j;
        }
        ++j;
      }
    }
    return cost[sink] != infCost;
  }
  pair<T, G> minCostFlow()
  {
    fill(potentials.begin(), potentials.end(), 0);
    T minCost = 0;
    G totalFlow = 0;
    while (bellmanFord())
    {
      G flow = infFlow;
      for (int v = sink; v != source; v = prevVertex[v])
      {
        auto &e = graph[prevVertex[v]][prevEdge[v]];
        flow = min(flow, e.flow);
      }
      totalFlow += flow;
      for (int v = sink; v != source; v = prevVertex[v])
      {
        auto &e = graph[prevVertex[v]][prevEdge[v]];
        e.flow -= flow;
        graph[e.to][e.back].flow += flow;
        minCost += flow * e.cost;
      }
    }
    return make_pair(minCost, totalFlow);
  }
};

const int maxN = 100, maxM = 7;
char ss[maxM + 1];
string mat[maxN];
int n, m;
int di[4] = {0, 1, -1, 0};
int dj[4] = {1, 0, 0, -1};

/*
0 -[]> [1 : n*m] -[]> [1 + n*m : 2*n*m] -[]> [2*n*m + 1]
*/

int getVertex(int i, int j, int left)
{
  return 1 + left*n*m + i*m + j;
}

int main()
{
  while (~scanf("%d %d", &n, &m))
  {
    for (int i = 0; i < n; ++i)
    {
      scanf(" %s", ss);
      mat[i] = string(ss);
    }

    int vertices = 2*n*m + 2;
    int source = 0, sink = vertices - 1;
    MinCostFlow<int, int> mcf(vertices, source, sink);

    int blacks = 0;
    for (int i = 0; i < n; ++i)
      for (int j = 0; j < m; ++j)
        blacks += mat[i][j] == '#';

    for (int i = 0; i < n; ++i)
      for (int j = 0; j < m; ++j)
      {
        if (mat[i][j] == '#')
        {
          mcf.addEdge(source, getVertex(i, j, 0), blacks, 0);
          for (int d = 0; d < 4; ++d)
          {
            int ni = i + di[d], nj = j + dj[d];
            if (ni < 0 || nj < 0 || ni >= n || nj >= m)
              continue;
            mcf.addEdge(getVertex(i, j, 0), getVertex(ni, nj, 1), blacks * blacks, 0);
          }
        }

        for (int d = 0; d < 4; ++d)
        {
          int ni = i + di[d], nj = j + dj[d];
          if (ni < 0 || nj < 0 || ni >= n || nj >= m)
            continue;
          mcf.addEdge(getVertex(i, j, 1), getVertex(ni, nj, 1), blacks * blacks, 1);
        }
      }

    for (int i = 0; i < n; ++i)
      for (int j = 0; j < m; ++j)
        if (mat[i][j] == '#')
          mcf.addEdge(getVertex(i, j, 1), sink, blacks, 0);

    const auto [cost, flow] = mcf.minCostFlow();
    assert(flow == blacks * blacks);
    printf("%d\n", cost);
  }
  return 0;
}
