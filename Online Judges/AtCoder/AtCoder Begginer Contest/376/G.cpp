#include <bits/stdc++.h>
#define DEBUG if (0)
#define DEBUG2 if (0)
#define lli long long int
#define ldouble long double

const lli kMod = 998244353LL;

lli ModExp(lli x, lli y) {
  lli ans = 1;
  while (y) {
    if (y & 1) ans = ans * x % kMod;
    x = x * x % kMod, y >>= 1;
  }
  return ans;
}
lli ModInverse(const lli x) { return ModExp(x, kMod - 2); }

struct DSU {
  int size;
  std::vector<int> parents;

  std::vector<int> a, p;
  std::vector<std::list<int>> ans;
  std::vector<lli> sum;

  DSU() : size(0) { parents.clear(), ans.clear(), sum.clear(); }
  DSU(const int sz, const std::vector<int>& a_, const std::vector<int>& p_)
      : size(sz), a(a_), p(p_) {
    Init();
  }
  void Init() {
    parents.resize(size, -1);
    ans.resize(size, {});
    sum.resize(size, 0);
    for (int i = 0; i < size; ++i) {
      ans[i].emplace_back(i);
      sum[i] = a[i];
    }
  }
  int Root(const int u) {
    if (parents[u] < 0) return u;
    const int new_root = Root(parents[u]);
    ans[new_root].splice(ans[new_root].end(), ans[u]);
    return parents[u] = new_root;
  }
  void Merge(int u, int v) {
    u = Root(u), v = Root(v);
    if (u == v) return;
    ans[u].splice(ans[u].end(), ans[v]);
    if (parents[u] > parents[v]) std::swap(u, v);

    DEBUG2 std::cout << "\tMerging " << u << " " << v << "\n";
    DEBUG2 {
      std::cout << "\t\tu:";
      for (const int i : ans[u]) std::cout << " " << i;
      std::cout << "\n";
      std::cout << "\t\tv:";
      for (const int i : ans[v]) std::cout << " " << i;
      std::cout << "\n";
    }

    parents[u] += parents[v];
    parents[v] = u;

    sum[u] += sum[v];
  }
  int SetSize(int u) { return -parents[Root(u)]; }
  bool SameSet(int u, int v) { return Root(u) == Root(v); }
  double Weight(const int u) {
    const int r = Root(u);
    return (double)sum[r] / (-parents[r]);
  }
};

struct TestCase {
  int n;
  std::vector<int> p, a;
  lli a_sum, inv_a_sum;
  std::vector<std::vector<int>> tree;

  void PrintTree(const int u = 0, const int depth = 0) {
    for (int i = 0; i < depth; ++i) std::cout << "  ";
    std::cout << u << " (" << a[u] << ")" << "\n";
    for (const int v : tree[u]) PrintTree(v, depth + 1);
  }

  DSU dsu;
  struct State {
    int u;
    double weight;
    int version;
    bool operator<(const State& other) const { return weight < other.weight; }
  };
  std::vector<int> FindBestOrder() {
    dsu = DSU(n, a, p);

    std::vector<int> inqueue_version(n, 0);
    std::priority_queue<State> cost_nodes;
    for (int i = 0; i < n; ++i) {
      cost_nodes.emplace(i, (double)a[i], inqueue_version[i]);
    }
    while (!cost_nodes.empty()) {
      const State s = cost_nodes.top();
      cost_nodes.pop();

      const int u = s.u, version = s.version;
      const double w = s.weight;
      if (version != inqueue_version[u]) continue;
      if (p[u] == -1) continue;

      DEBUG2 std::cout << "\t\t" << p[u] << " " << u << " | " << w << " "
                       << dsu.SetSize(p[u]) << " " << dsu.sum[p[u]] << "\n";
      dsu.Merge(p[u], u);
      const int nxt = p[u];
      ++inqueue_version[nxt];
      cost_nodes.emplace(nxt, dsu.Weight(nxt), inqueue_version[nxt]);
    }

    const auto& res = dsu.ans[dsu.Root(0)];
    return std::vector<int>(res.begin(), res.end());
  }

  lli ComputeExpectedOperations(const std::vector<int>& order) {
    DEBUG {
      std::cout << "\t";
      for (const int o : order) std::cout << o << " ";
      std::cout << "\n";
    }
    std::fflush(stdout);
    assert((int)order.size() == n);
    lli ans = 0;
    for (int i = 0; i < n; ++i) {
      DEBUG std::cout << "\t" << i << " " << order[i] << " " << a[order[i]]
                      << "\n";
      ans = (ans + (lli)i * a[order[i]] % kMod) % kMod;
    }
    DEBUG std::cout << "\t\t" << ans << "\n";
    ans = ans * inv_a_sum % kMod;
    return ans;
  }

  void Run() {
    std::cin >> n;
    ++n;

    p.resize(n);
    p[0] = -1;
    for (int i = 1; i < n; ++i) std::cin >> p[i];

    a.resize(n);
    a[0] = 0;
    a_sum = 0;
    for (int i = 1; i < n; ++i) {
      std::cin >> a[i];
      a_sum += a[i];
    }
    inv_a_sum = ModInverse(a_sum);

    tree.resize(n);
    for (int i = 1; i < n; ++i) {
      tree[p[i]].push_back(i);
    }

    DEBUG PrintTree();

    std::vector<int> best_order = FindBestOrder();
    const lli ans = ComputeExpectedOperations(best_order);
    std::cout << ans << "\n";
  }
};
TestCase test_case;

int main() {
  int test_cases;
  std::cin >> test_cases;
  for (int t = 1; t <= test_cases; ++t) {
    test_case = TestCase{};
    test_case.Run();
  }
  return 0;
}
