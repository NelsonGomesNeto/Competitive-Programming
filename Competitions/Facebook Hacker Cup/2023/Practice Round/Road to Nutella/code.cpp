#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int inf = numeric_limits<int>::max();
const int kMaxN = 3e5;
int n, m, q;
vector<pair<int, int>> graph[kMaxN];

/*
Idea:
Instead of forcing u to be strictly inside the cycle.
We could take advantage of Dfs to find and update the path with duplicate edges (in the return)
And in the Dfs, go through paths in this order:
not visited
visited

So that we only go over duplicates when we really need to.                               j
*/

namespace solver {
int memo[kMaxN];
namespace dfs {
int visited[2][kMaxN];
namespace internal {
void Dfs(int u, int prv = -1, bool turn = true, int dist = 1) {
  DEBUG printf("\t\t\t%d %d %d | %d\n", u + 1, turn, dist, visited[turn][u]);
  if (visited[!turn][u]) {
    memo[u] = 0;
    return;
  }
  if (visited[turn][u]) {
    return;
  }

  visited[turn][u] = dist;

  list<int> to_visit[2];
  for (auto [v, ei] : graph[u]) {
    if (v == prv) continue;
    to_visit[visited[!turn][v] == 0].push_back(v);
  }

  for (int i = 0; i < 2; ++i)
    for (int v : to_visit[i]) {
      Dfs(v, u, !turn, dist + 1);
    }

  visited[turn][u] = -dist;
}
}
void Dfs(int u) {
  for (int i = 0; i < 2; ++i)
    fill(visited[i], visited[i]+n, 0);
  internal::Dfs(u);
}
}

namespace propagate {
bool visited[kMaxN];
void Bfs(int source) {
  fill(visited, visited+n, false);
  queue<pair<int, int>> q;
  q.emplace(source, 0);
  while (!q.empty()) {
    auto [u, d] = q.front();
    q.pop();

    if (source != u && memo[u] == 0) continue;
    else memo[u] = min(memo[u], d);

    if (visited[u]) continue;
    visited[u] = true;
    for (auto [v, _] : graph[u])
      q.emplace(v, d + 1);
  }
}
}

void Precompute() {
  fill(memo, memo+n, inf);

  bool has = false;
  for (int i = 0; i < n; ++i) {
    if (memo[i] == inf) {
      dfs::Dfs(i);
    }
    if (memo[i] != inf) has = true;
  }

  if (!has) return;

  for (int i = 0; i < n; ++i) {
    if (memo[i] == 0) {
      propagate::Bfs(i);
    }
  }
}

namespace min_path {
bool visited[kMaxN];
int Bfs(int source, int target) {
  fill(visited, visited+n, false);
  queue<pair<int, int>> q;
  q.emplace(source, memo[source]);
  while (!q.empty()) {
    auto [u, dup] = q.front();
    q.pop();

    if (u == target) return dup;
    if (visited[u]) continue;
    visited[u] = true;

    for (auto [v, _] : graph[u])
      q.emplace(v, min(dup, memo[v]));
  }
  assert(source && target && false);
}
}
int BuggyRoad(int u, int v) {
  int res = min_path::Bfs(u, v);
  printf("\t%d %d | %d\n", u + 1, v + 1, res);
  return res == inf ? -1 : res;
}
}

namespace lol {
bool visited[2][kMaxN];
int Solve(int source, int target) {
  for (int i = 0; i < 2; ++i)
    fill(visited[i], visited[i]+n, false);
  queue<tuple<int, bool, int>> q;
  q.emplace(source, true, 0);
  while (!q.empty()) {
    auto [u, turn, dup] = q.front();
    q.pop();

    if (u == target && !turn) return dup;
    visited[turn][u] = true;

    list<int> to_visit[2];
    for (auto [v, _] : graph[u])
      to_visit[visited[!turn][v]].push_back(v);
    for (int i = 0; i < 2; ++i)
      for (int v : to_visit[i])
        q.emplace(v, !turn, dup + i);
  }
  return -1;
}
}

int main() {
  int test_cases;
  scanf("%d", &test_cases);
  for (int test_case = 1; test_case <= test_cases; ++test_case) {
    scanf("%d %d", &n, &m);
    fill(graph, graph+n, vector<pair<int, int>>());
    for (int i = 0; i < m; ++i) {
      int u, v;
      scanf("%d %d", &u, &v);
      --u, --v;
      graph[u].emplace_back(v, i), graph[v].emplace_back(u, i);
    }

    // solver::Precompute();

    scanf("%d", &q);
    lli ans = 0;
    for (int i = 0; i < q; ++i) {
      int u, v;
      scanf("%d %d", &u, &v);
      --u, --v;
      ans += lol::Solve(u, v);
    }
    printf("Case #%d: %lld\n", test_case, ans); fflush(stdout);
  }
  return 0;
}
