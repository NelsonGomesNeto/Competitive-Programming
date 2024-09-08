#include <bits/stdc++.h>
#define DEBUG if(1)
#define lli long long int
#define ldouble long double
using namespace std;

/*
For every set S, there is a set of equations:
{
  x[a[i]] - x[b[i]] = d[i]
}

If we build a graph with edges (a[i], b[i]) and cost d[i]:
All cycles must sum 0.
*/

struct DSU
{
  int size;
  vector<int> parents;
  vector<lli> sum;
  DSU() { parents.clear(), sum.clear(); }
  DSU(int sz) : size(sz) { init(); }
  void init() { parents.resize(size, -1), sum.resize(size, 0); }
  int root(int u) {
    if (parents[u] < 0) {
      return u;
    }
    parents[u] = root(parents[u]);
    sum[u] += sum[parents[u]];
    return parents[u];
  }
  void merge(int u, int v, lli d)
  {
    int ou = u, ov = v;
    u = root(u), v = root(v);
    if (u == v) return;
    if (parents[u] > parents[v]) swap(u, v), swap(ou, ov), d = -d;
    parents[u] += parents[v];
    sum[ov] += sum[ou] - d;
    DEBUG printf("\t\tmerge %d <- %d | %lld | %d %lld\n", u + 1, v + 1, d, ov + 1, sum[ov]);
    parents[v] = u;
  }
  bool possible(int u, int v, lli d) {
    // u = root(u), v = root(v);
    // if (u == v) return true;
    // if (parents[u] > parents[v]) swap(u, v), d = -d;
    DEBUG printf("\t%d %d %lld | %lld %lld\n", u + 1, v + 1, d, sum[u], sum[v]);
    return sum[u] == sum[v] + d;
  }
  int setSize(int u) { return -parents[root(u)]; }
  lli setSum(int u) { return sum[root(u)]; }
  bool sameSet(int u, int v) { return root(u) == root(v); }
};
DSU dsu;

const int kMaxN = 2e5;
int n, queries;
struct Triplet {
  int a, b; lli d;
  void Read() {
    scanf("%d %d %lld", &a, &b, &d);
    --a, --b;
  }
};
vector<Triplet> ts;

vector<vector<pair<int, lli>>> graph;
int visited[kMaxN], version;
bool bfs(int source, int target, lli dist) {
  ++version;
  queue<pair<int, lli>> q;
  q.emplace(target, dist);
  while (!q.empty()) {
    auto [u, curr] = q.front();
    q.pop();
    if (u == source) return curr == 0;
    if (visited[u] == version) continue;
    visited[u] = version;

    for (auto [v, d] : graph[u]) {
      q.emplace(v, curr + d);
    }
  }
  return false;
}

int main() {
  while (~scanf("%d %d", &n, &queries)) {
    graph.clear();
    graph.resize(n);
    ts.resize(queries);
    for (auto& t : ts) t.Read();

    dsu = DSU(n);
    vector<int> s;
    map<pair<int, int>, lli> included;
    auto add = [&s, &included](int i) {
      int u = ts[i].a, v = ts[i].b; lli d = ts[i].d;
      dsu.merge(u, v, d);
      included[{u, v}] = d;
      included[{v, u}] = -d;
      graph[u].emplace_back(v, d);
      graph[v].emplace_back(u, -d);
      s.push_back(i);
    };

    fill(visited, visited+n, 0), version = 0;
    for (int i = 0; i < queries; ++i) {
      int u = ts[i].a, v = ts[i].b; lli d = ts[i].d;
      if (included.count({u, v})) {
        if (included[{u, v}] == d) add(i);
        continue;
      }
      if (u == v) {
        if (d == 0) add(i);
        continue;
      }
      if (dsu.sameSet(u, v) && !dsu.possible(u, v, d)) {
        continue;
      }
      add(i);
    }

    for (int i = 0; i < s.size(); ++i) {
      printf("%d%c", s[i] + 1, i + 1 < s.size() ? ' ' : '\n');
    }
  }
  return 0;
}
