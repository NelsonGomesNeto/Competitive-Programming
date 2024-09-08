#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxX = 1e6 + 1;
const lli mod = 998244353;

lli fat[maxX], invFat[maxX];
lli modPow(lli x, lli y)
{
  lli ans = 1;
  while (y)
  {
    if (y & 1LL) ans = ans * x % mod;
    x = x * x % mod, y >>= 1LL;
  }
  return ans;
}
lli inv(lli x)
{
  return modPow(x, mod - 2);
}
lli choose(lli nn, lli kk)
{
  if (nn < kk) return 0;
  if (nn < mod) return fat[nn] * invFat[kk] % mod * invFat[nn - kk] % mod;
  lli ans = 1;
  while (nn || kk)
  {
    lli nnn = nn % mod, kkk = kk % mod;
    nn /= mod, kk /= mod;
    ans = ans * choose(nnn, kkk) % mod;
  }
  return ans;
}
// nn = stars, kk = bars
lli starsAndBars(lli nn, lli kk)
{
  return choose(nn + kk, kk);
}

// source (0) -[a[i]]> types_i (1 : n) -[a[i] (if c[i][j])]> company_j (1 + n : n + m) -[b[j]]> sink (n + m + 1)
template<typename T>
struct Edge { int to, back; T flow, capacity; };

template<typename T>
struct Dinic
{
  int source, sink, vertices; T inf;
  vector<int> level, ptr;
  vector<vector<Edge<T>>> graph;

  Dinic() { }
  Dinic(int vertices, int source, int sink, T inf) : vertices(vertices), source(source), sink(sink), inf(inf)
  {
    graph.resize(vertices, vector<Edge<T>>());
    level.resize(vertices);
    ptr.resize(vertices);
  }

  void addEdge(int u, int v, T f)
  {
    graph[u].push_back({v, (int)graph[v].size(), f, f});
    graph[v].push_back({u, (int)graph[u].size() - 1, 0, 0});
  }

  bool bfs()
  {
    fill(level.begin(), level.end(), -1);
    level[source] = 0;
    queue<int> q; q.push(source);
    while (!q.empty())
    {
      int u = q.front(); q.pop();
      for (auto &e: graph[u])
        if (e.flow && level[e.to] == -1)
          q.push(e.to), level[e.to] = level[u] + 1;
    }
    return level[sink] != -1;
  }

  T dfs(int u, T flow)
  {
    if (u == sink || flow == 0)
      return flow;

    for (int &p = ptr[u]; p < graph[u].size(); p++)
    {
      auto &e = graph[u][p];
      if (e.flow && level[u] == level[e.to] - 1)
      {
        T delivered = dfs(e.to, min(flow, e.flow));
        e.flow -= delivered;
        graph[e.to][e.back].flow += delivered;
        if (delivered)
          return delivered;
      }
    }
    return 0;
  }

  T flow()
  {
    T maxFlow = 0, flow;
    while (bfs())
    {
      fill(ptr.begin(), ptr.end(), 0);
      while (flow = dfs(source, inf))
        maxFlow += flow;
    }
    return maxFlow;
  }
};

Dinic<int> dinic;

const int maxN = 20, maxM = 1e4, maxA = 1e5; int n, m;
int a[maxN], b[maxM];
bool c[maxN][maxM];

void buildDinicGraph()
{
  for (int i = 0; i < dinic.vertices; i++) dinic.graph[i].clear();

  for (int i = 0; i < n; i++)
    dinic.addEdge(dinic.source, 1 + i, a[i]);
  for (int i = 0; i < n; i++)
    for (int j = 0; j < m; j++)
      if (c[i][j])
        dinic.addEdge(1 + i, 1 + n + j, a[i]);
  for (int j = 0; j < m; j++)
    dinic.addEdge(1 + n + j, dinic.sink, b[j]);
}
int totalB;
bool can(int i, int rem)
{
  if (rem > a[i]) return false;
  a[i] -= rem;
  buildDinicGraph();
  a[i] += rem;
  return dinic.flow() >= totalB;
}

lli memo[maxN][maxA + 1];
lli solve(int toRem, int i = 0)
{
  if (toRem == 0) return !can(0, 0);
  if (i == n) return 0;
  // lli &ans = memo[i][toRem];
  // if (ans != -1) return ans;

  lli ans = 0;
  int backup = a[i];
  for (int j = min(a[i], toRem); j >= 0; j--)
  {
    a[i] = backup - j;
    ans = (ans + solve(toRem - j, i + 1) * choose(backup, j) % mod) % mod;
  }
  a[i] = backup;
  return ans;
}

int main()
{
  fat[0] = 1;
  for (lli i = 1; i < maxX; i++)
    fat[i] = i * fat[i - 1] % mod;
  for (int i = 0; i < maxX; i++)
    invFat[i] = inv(fat[i]);

  while (~scanf("%d %d", &n, &m))
  {
    for (int i = 0; i < n; i++) scanf("%d", &a[i]);
    for (int i = 0; i < m; i++) scanf("%d", &b[i]);
    for (int i = 0; i < n; i++)
      for (int j = 0; j < m; j++)
      {
        int cc; scanf("%d", &cc);
        c[i][j] = cc;
      }

    dinic = Dinic<int>(n + m + 2, 0, n + m + 1, 1e8);
    buildDinicGraph();

    int maxFlow = dinic.flow();
    DEBUG printf("maxFlow: %d\n", maxFlow);

    totalB = 0; for (int i = 0; i < m; i++) totalB += b[i];
    if (maxFlow < totalB)
    {
      printf("0 1\n");
    }
    else
    {
      DEBUG
        for (int i = 0; i < n; i++)
        {
          printf("\t%d\n", i);
          for (auto &e: dinic.graph[1 + i])
            if (e.to >= 1 + n && e.to <= 1 + n + m - 1 && e.flow != e.capacity)
              printf("\t\t%d bought %d\n", e.to - n - 1, e.capacity - e.flow);
            else if (e.to == dinic.source)
              printf("\t\tleft: %d\n", a[i] - e.flow);
        }

      int minimum = maxA;
      for (int i = 0; i < n; i++)
      {
        int lo = 0, hi = a[i] + 1;
        while (lo < hi)
        {
          int mid = (lo + hi) >> 1;
          if (!can(i, mid)) hi = mid;
          else lo = mid + 1;
        }
        if (lo != a[i] + 1)
          minimum = min(minimum, lo);
      }
      // memset(memo, -1, sizeof(memo));
      lli ans = solve(minimum);
      printf("%d %lld\n", minimum, ans);
    }
    DEBUG printf("---------------------\n");
  }
  return 0;
}