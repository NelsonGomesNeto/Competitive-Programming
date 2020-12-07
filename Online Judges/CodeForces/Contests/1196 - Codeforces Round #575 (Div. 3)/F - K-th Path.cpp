#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
using namespace std;

const int maxN = 2e5; int n, m, k;
vector<pair<int, lli>> graph[maxN];
set<set<int>> paths;
set<pair<int, int>> done;
struct Node
{
  int u; lli dist; set<int> path; int start;
  bool operator<(const Node &node) const
  {
    return(dist < node.dist || (dist == node.dist && u < node.u) || (dist == node.dist && u == node.u && start < node.start));// || (dist == node.dist && u == node.u && start == node.start && path < node.path));
  }
};

lli solve()
{
  set<Node> pq;
  for (int i = 0; i < n; i ++)
    for (auto &e: graph[i])
    {
      if (pq.size() >= k && e.second > prev(pq.end())->dist) continue;
      pq.insert({e.first, e.second, {i}, i});
    }
  while (!pq.empty())
  {
    Node now = *pq.begin();
    int u = now.u, start = now.start; lli d = now.dist; set<int> path = now.path;
    pq.erase(now);
    pair<int, int> fromTo = {min(u, start), max(u, start)}; path.insert(u);
    done.insert(fromTo), paths.insert(path);
    DEBUG {
      printf("%d %lld %d %d -", u + 1, d, (int) path.size(), (int) done.size());
      for (int v: path) printf(" %d", v + 1); printf("\n");
    }
    if (done.size() == k) return(d);
    for (auto &e: graph[u])
    {
      if (path.count(e.first)) continue;
      lli newDist = d + e.second;
      if (pq.size() >= k && newDist > prev(pq.end())->dist) continue;
      pq.insert({e.first, newDist, path, start});
    }
  }
  return(LONG_LONG_MIN);
}

int main()
{
  scanf("%d %d %d", &n, &m, &k);
  for (int i = 0; i < m; i ++)
  {
    int u, v; lli c; scanf("%d %d %lld", &u, &v, &c); u --, v --;
    graph[u].push_back({v, c}), graph[v].push_back({u, c});
  }

  lli ans = solve();
  printf("%lld\n", ans);

  return(0);
}