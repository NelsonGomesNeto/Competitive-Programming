#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

template <typename T>
struct FastQueue
{
  FastQueue() {}
  FastQueue(int reservedSize) : q(reservedSize) { clear(); }

  void clear() { f = i = sz = 0; }

  void push(int e)
  {
    q[i++] = e;
    if (i == q.size()) i = 0;
    // assert(f != i);
    // ++sz;
  }
  void pop()
  {
    ++f;
    if (f == q.size()) f = 0;
    // --sz;
  }
  T front() { return q[f]; }
  bool empty() { return f == i; }
  // bool empty() { return sz == 0; }
  int size() { return sz; }

  int f, i, sz;
  vector<T> q;
};

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

  FastQueue<int> fastQueue;

  MinCostFlow() {}
  MinCostFlow(int vertices, int source, int sink, G infFlow = numeric_limits<G>::max(), T infCost = numeric_limits<T>::max())
      : vertices(vertices), source(source), sink(sink), infFlow(infFlow), infCost(infCost)
  {
    graph.resize(vertices, vector<Edge<T, G>>());
    prevVertex.resize(vertices), prevEdge.resize(vertices);
    cost.resize(vertices);

    inqueue.resize(vertices);

    potentials.resize(vertices), visited.resize(vertices);

    fastQueue = FastQueue<int>(vertices);
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
    // queue<int> q;
    FastQueue<int>& q = fastQueue;
    q.clear();
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
    while (SPFA())
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

// source(0) -[a[i]]> pos(1 : n) -[a[i]]> adjacentAndSelfPos(1 + n : 2*n) -[limit]> sink(2*n + 1)

const int maxN = 5e3;
int n;
lli a[maxN];

int main()
{
  while (~scanf("%d", &n))
  {
    lli total = 0;
    for (int i = 0; i < n; ++i)
      scanf("%lld", &a[i]);
    const lli minimum = abs(*min_element(a, a+n));
    for (int i = 0; i < n; ++i)
    {
      a[i] += minimum;
      total += a[i];
    }
    const lli lo = total / n, hi = total / n + 1;

    MinCostFlow<lli, lli> mcf(n + 2, 0, n + 1);
    for (int i = 0; i < n; ++i)
      mcf.addEdge(mcf.source, 1 + i, a[i], 0);

    for (int i = 0; i < n; ++i)
    {
      // mcf.addEdge(1 + i, 1 + n + i, a[i], 0);
      if (i)
        mcf.addEdge(1 + i, 1 + i - 1, mcf.infFlow, 1);
      if (i + 1 < n)
        mcf.addEdge(1 + i, 1 + i + 1, mcf.infFlow, 1);
      // for (int j = i + 1; j < n; ++j)
      //   if (j != i)
      //     mcf.addEdge(1 + n + i, 1 + n + j, mcf.infFlow, abs(i - j));
    }

    for (int i = 0; i < n; ++i)
      mcf.addEdge(1 + i, mcf.sink, lo, 0);

    const auto [cost, flow] = mcf.minCostFlow();
    lli rem = total - flow;
    // assert(~rem & 1);
    // rem >>= 1;

    DEBUG {
      printf("flow: %lld | total: %lld, flow: %lld, rem: %lld | %lld %lld\n", cost, total, flow, rem, lo, hi);
      for (int i = 0; i < n; ++i)
      {
        printf("\t%d - %lld %lld | %lld\n", i, a[i], mcf.graph[mcf.sink][i].flow, mcf.graph[mcf.source][i].flow);
      }
    }
    lli ans = cost;
    for (int i = 0; i < n; ++i)
      if (mcf.graph[mcf.source][i].flow > 1)
        ans += mcf.graph[mcf.source][i].flow - 1;
    printf("%lld\n", ans);
  }
  return 0;
}
