#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
using namespace std;

template<typename T, typename G>
struct Edge
{
  int to, back;
  G flow;
  T cost;
};

template<typename T, typename G>
struct MinCostFlow
{
  int source, sink, vertices; G infFlow; T infCost;
  vector<int> prevVertex, prevEdge;
  vector<T> cost;
  vector<vector<Edge<T, G>>> graph;

  vector<bool> inqueue;

  vector<T> potentials;
  vector<bool> visited;

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
  bool SPFA()
  {
    fill(inqueue.begin(), inqueue.end(), false);
    fill(cost.begin(), cost.end(), infCost);
    queue<int> q; q.push(source); cost[source] = 0;
    while (!q.empty())
    {
      int u = q.front(); q.pop(); inqueue[u] = false;
      int j = 0;
      for (const auto& e: graph[u])
      {
        T newCost = cost[u] + e.cost;
        if (e.flow && newCost < cost[e.to])
        {
          if (!inqueue[e.to]) inqueue[e.to] = true, q.push(e.to);
          cost[e.to] = newCost;
          prevVertex[e.to] = u, prevEdge[e.to] = j;
        }
        ++j;
      }
    }
    return cost[sink] != infCost;
  }
  bool dijkstraWithPotentials()
  {
    fill(visited.begin(), visited.end(), false);
    fill(cost.begin(), cost.end(), infCost);
    priority_queue<pair<T, int>> pq;
    pq.push({0, source}); cost[source] = 0;
    while (!pq.empty())
    {
      int u = pq.top().second; pq.pop();
      if (visited[u]) continue;
      visited[u] = true;
      int j = 0;
      for (const auto& e: graph[u])
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
  pair<T, G> minCostFlow()
  {
    fill(potentials.begin(), potentials.end(), 0);
    T minCost = 0; G totalFlow = 0;
    while (SPFA())
    {
      G flow = infFlow;
      for (int v = sink; v != source; v = prevVertex[v])
      {
        auto& e = graph[prevVertex[v]][prevEdge[v]];
        flow = min(flow, e.flow);
      }
      totalFlow += flow;
      for (int v = sink; v != source; v = prevVertex[v])
      {
        auto& e = graph[prevVertex[v]][prevEdge[v]];
        e.flow -= flow;
        graph[e.to][e.back].flow += flow;
        minCost += flow * e.cost;
      }
    }
    return make_pair(minCost, totalFlow);
  }
};
MinCostFlow<lli, int> mcf;

template<typename T>
struct Hungarian {
  int n;
  vector<vector<T>> costs;
  vector<T> u, v;
  vector<int> p, way;
  T inf;

  Hungarian() {}
  Hungarian(int n) : n(n), u(n+1), v(n+1), p(n+1), way(n+1)
  {
    inf = numeric_limits<T>::max();
    costs.resize(n, vector<T>(n, 0));
  }
  pair<T, vector<int>> assignment()
  {
    for (int i = 1; i <= n; i++) {
      p[0] = i;
      int j0 = 0;
      vector<T> minv(n+1, inf);
      vector<int> used(n+1, 0);
      do {
        used[j0] = true;
        int i0 = p[j0], j1 = -1;
        T delta = inf;
        for (int j = 1; j <= n; j++) if (!used[j]) {
          T cur = costs[i0-1][j-1] - u[i0] - v[j];
          if (cur < minv[j]) minv[j] = cur, way[j] = j0;
          if (minv[j] < delta) delta = minv[j], j1 = j;
        }
        for (int j = 0; j <= n; j++)
          if (used[j]) u[p[j]] += delta, v[j] -= delta;
          else minv[j] -= delta;
        j0 = j1;
      } while (p[j0] != 0);
      do {
        int j1 = way[j0];
        p[j0] = p[j1];
        j0 = j1;
      } while (j0);
    }
    vector<int> ans(n);
    for (int j = 1; j <= n; j++) ans[p[j]-1] = j-1;
    return make_pair(-v[0], ans);
  }
};
Hungarian<lli> hungarian;

const int maxN = 500; int n, safeN;
lli cost[maxN][maxN];

void minCostFlowSolve()
{
  mcf = MinCostFlow<lli, int>(safeN + 2, 0, safeN + 1);
  for (int i = 0; i < n; i += 2)
  {
    mcf.addEdge(mcf.source, 1 + (i >> 1), 1, 0);
    mcf.addEdge(1 + (safeN >> 1) + (i >> 1), mcf.sink, 1, 0);
  }

  for (int i = 0; i < n; i += 2)
    for (int j = 0; j < n; j += 2)
    {
      lli c = 0;
      if (j - 1 >= 0) c += cost[i][j - 1];
      if (j + 1 < n) c += cost[i][j + 1];
      mcf.addEdge(1 + (i >> 1), 1 + (safeN >> 1) + (j >> 1), 1, c);
    }

  auto ans = mcf.minCostFlow();
  printf("%lld\n", ans.first);
}

void hungarianSolve()
{
  hungarian = Hungarian<lli>(safeN >> 1);
  for (int i = 0; i < n; i += 2)
  {
    for (int j = 0; j < n; j += 2)
    {
      lli c = 0;
      if (j - 1 >= 0) c += cost[i][j - 1];
      if (j + 1 < n) c += cost[i][j + 1];
      hungarian.costs[i >> 1][j >> 1] = c;
    }
  }
  auto ans = hungarian.assignment();
  DEBUG for (int i = 0; i < ans.second.size(); i++)
      printf("%d - %d\n", i, ans.second[i]);
  printf("%lld\n", ans.first);
}

int main()
{
  // cin required
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  // while (~scanf("%d", &n))
  while (cin >> n)
  {
    for (int i = 0; i < n; i++)
      for (int j = 0; j < n; j++)
        // scanf("%lld", &cost[i][j]);
        cin >> cost[i][j];

    safeN = n;
    if (safeN & 1) safeN++;

    // Hungarian
    // hungarianSolve();

    // MinCostFlow
    minCostFlowSolve();
  }
  return 0;
}