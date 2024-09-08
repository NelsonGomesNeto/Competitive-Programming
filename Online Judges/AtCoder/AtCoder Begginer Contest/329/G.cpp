#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const lli mod = 998244353;
const int kMaxN = 1e4, kMaxK = 1e3, kMaxM = 2e5;
int n, m, k;

int p[kMaxN];
vector<int> tree[kMaxN];

vector<int> dest[kMaxN];
struct Ball {
  int s, t;
  void Read() {
    scanf("%d %d", &s, &t); --s, --t;
    dest[s].push_back(t);
  }
};
Ball balls[kMaxM];

// multiset<int> basket;
int visited[kMaxN];
map<tuple<int, int, int, int>, lli> memo;
lli Dfs(int u = 0, int prv = -1, multiset<int> basket = {}) {
  // path.emplace_back(u, visited[u]);
  if (basket.count(u)) {
    basket.erase(u);
  }
  if (dest[u].size()) {
    if (dest[u].size() + basket.size() > k) {
      return 0;
    }
    basket.insert(dest[u].begin(), dest[u].end());
  }

  // tuple<int, int, int, int> state = {u, prv, visited[u], basket.size()};
  // if (memo.count(state)) return memo[state];
  // lli& ans = memo[state];
  // ans = 0;
  lli ans = 0;

  if (visited[u] == tree[u].size()) {
    if (u == 0) {
      // printf("\tpath:");
      // for (auto [v, vis] : path) printf(" (%d, %d)", v + 1, vis);
      // printf("\n");
      return basket.empty();
    }
    return Dfs(p[u], u, basket);
  }
  ++visited[u];

  if (tree[u].size() == 1) {
    ans = Dfs(tree[u][0], u, basket);
  } else if (tree[u].size() == 2) {
    if (tree[u][0] == prv) {
      ans = Dfs(tree[u][1], u, basket);
    } else if (tree[u][1] == prv) {
      ans = Dfs(tree[u][0], u, basket);
    } else {
      // I need some way to efficiently store the basket state.
      multiset<int> prev = basket;
      ans = Dfs(tree[u][0], u, basket);
      basket = prev;
      ans = (ans + Dfs(tree[u][1], u, basket)) % mod;
    }
  }
  --visited[u];

  return ans;
}

int main() {
  while (~scanf("%d %d %d", &n, &m, &k)) {
    for (int i = 0; i < n; ++i) {
      tree[i].clear();
      dest[i].clear();
    }
    for (int i = 1; i < n; ++i) {
      scanf("%d", &p[i]);
      --p[i];
      tree[p[i]].push_back(i);
    }

    for (int i = 0; i < m; ++i)
      balls[i].Read();

    // basket.clear();
    fill(visited, visited+n, 0);
    memo.clear();
    lli ans = Dfs();
    printf("%lld\n", ans);
  }
  return 0;
}
