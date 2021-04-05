#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 1e5; int n;
const lli inf = LONG_LONG_MAX;
struct City
{
  lli a, c;
  void read() { scanf("%lld %lld", &a, &c); }
  void print(string pre = "") { printf("%s%lld %lld\n", pre.c_str(), a, c); }
  bool operator<(const City &other) const { return a < other.a; }
};
City cities[maxN];

lli getCost(int i, int j)
{
  // max(c[i], a[j] - a[i])
  return max(0LL, cities[j].a - (cities[i].a + cities[i].c));
}

vector<pair<int, lli>> graph[maxN];
int upperBound(int target, int lo = 0, int hi = n - 1)
{
  while (lo < hi)
  {
    int mid = (lo + hi + 1) >> 1;
    if (cities[mid].a <= target) lo = mid;
    else hi = mid - 1;
  }
  return cities[lo].a <= target ? lo : -1;
}
void buildGraph()
{
  for (int i = 0; i < n; i++)
  {
    graph[i].clear();

    lli limit = cities[i].a + cities[i].c;
    int pos = upperBound(limit);
    if (pos >= 0)
    {
      if (i)
        graph[i].push_back({i - 1, 0});
      graph[i].push_back({pos, 0});
      if (pos + 1 < n)
        graph[i].push_back({pos + 1, getCost(i, pos + 1)});
    }
  }
}

lli dist[maxN];
void dijkstra(int source = 0)
{
  for (int i = 0; i < n; i++)
    dist[i] = inf;
  priority_queue<pair<lli, int>, vector<pair<lli, int>>, greater<pair<lli, int>>> pq;
  pq.push({dist[source] = 0, source});
  while (!pq.empty())
  {
    int u; lli d;
    tie(d, u) = pq.top(); pq.pop();
    if (d > dist[u]) continue;

    for (auto &[v, w]: graph[u])
      if (d + w < dist[v])
        pq.push({dist[v] = d + w, v});
  }
}

int main()
{
  while (~scanf("%d", &n))
  {
    lli base = 0;
    for (int i = 0; i < n; i++)
    {
      cities[i].read();
      base += cities[i].c;
    }
    sort(cities,cities+n);

    buildGraph();
    lli ans = base;
    dijkstra();
    ans += dist[n - 1];

    printf("%lld\n", ans);
  }
  return 0;
}
