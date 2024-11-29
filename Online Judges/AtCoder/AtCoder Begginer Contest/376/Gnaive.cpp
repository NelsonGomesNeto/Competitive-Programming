#include <bits/stdc++.h>
#define DEBUG if (0)
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
  std::vector<int> ans;
  DSU() : size(0) { parents.clear(), ans.clear(); }
  DSU(const int sz) : size(sz) { Init(); }
  void Init() {
    parents.resize(size, -1);
    // ans.resize();
  }
  int Root(const int u) {
    return parents[u] < 0 ? u : parents[u] = Root(parents[u]);
  }
  void Merge(int u, int v) {
    u = Root(u), v = Root(v);
    if (u == v) return;
    if (parents[u] > parents[v]) std::swap(u, v);
    parents[u] += parents[v];
    parents[v] = u;
  }
  int SetSize(int u) { return -parents[Root(u)]; }
  bool SameSet(int u, int v) { return Root(u) == Root(v); }
};

struct TestCase {
  int n;
  std::vector<int> p, a;
  lli a_sum, inv_a_sum;
  std::vector<std::vector<int>> tree;
  std::vector<int> requirements;

  lli PrintTree(const int u = 0, const int depth = 0, const lli sum_above = 0) {
    lli sum_below = a[u];
    for (const int v : tree[u])
      sum_below += PrintTree(v, depth + 1, sum_above + a[u]);
    for (int i = 0; i < depth; ++i) std::cout << "  ";
    std::cout << u << " (" << a[u] << ", " << sum_above << ", " << sum_below
              << ")" << "\n";
    return sum_below;
  }

  std::vector<lli> sum_to_root;
  void FillSumToRoot(const int u = 0, lli sum = 0) {
    sum += a[u];
    sum_to_root[u] = sum;
    for (const int v : tree[u]) FillSumToRoot(v, sum);
  }

  struct State {
    lli value;
    int version, u;
    lli above;
    bool operator<(const State& other) const {
      // return version > other.version ||
      //        (version == other.version && value > other.value);
      return value < other.value;
      // return value > other.value ||
      //        (value == other.value && above > other.above);
      // return above > other.above ||
      //        (above == other.above && value > other.value);
    }
  };
  std::vector<int> FindBestOrder() {
    std::vector<int> ans;

    std::priority_queue<State> pq;
    auto Enqueue = [&](const int u) {
      // std::cout << "\t\t\tenqueue " << u << " " << (n - 1 - ans.size()) <<
      // "\n";
      pq.emplace((lli)a[u] * (n - 1 - ans.size()), ans.size(), u);
    };
    for (int i = 0; i < n; ++i) {
      if (requirements[i] > 0) continue;
      Enqueue(i);
    }

    while (!pq.empty()) {
      const State s = pq.top();
      pq.pop();
      if (s.version > ans.size()) {
        Enqueue(s.u);
        continue;
      }
      ans.push_back(s.u);

      if (--requirements[p[s.u]] == 0) {
        Enqueue(p[s.u]);
      }
    }
    std::reverse(ans.begin(), ans.end());
    return ans;
  }
  std::vector<int> FindBestOrder2() {
    std::vector<int> ans;

    std::vector<State> pq;
    auto Enqueue = [&](const int u) {
      // std::cout << "\t\t\tenqueue " << u << " " << (n - 1 - ans.size()) <<
      // "\n";
      pq.emplace_back(0, ans.size(), u);
    };
    for (int i = 0; i < n; ++i) {
      if (requirements[i] > 0) continue;
      Enqueue(i);
    }

    while (!pq.empty()) {
      for (State& ns : pq) {
        ns.version = ans.size();
        ns.value = (lli)a[ns.u] * (n - 1 - ns.version);
        ns.above = sum_to_root[ns.u] * (n - 1 - ns.version);
      }
      std::sort(pq.begin(), pq.end());
      const State s = pq.back();
      pq.pop_back();
      ans.push_back(s.u);

      if (--requirements[p[s.u]] == 0) {
        Enqueue(p[s.u]);
      }
    }
    std::reverse(ans.begin(), ans.end());
    return ans;
  }
  std::vector<int> FindBestOrder3() {
    std::vector<int> ans;

    std::priority_queue<State> pq;
    auto Enqueue = [&](const int u) {
      // std::cout << "\t\t\tenqueue " << u << " " << (n - 1 - ans.size()) <<
      // "\n";
      pq.emplace((lli)a[u] * ans.size(), ans.size(), u);
    };
    Enqueue(0);
    while (!pq.empty()) {
      // for (State& ns : pq) {
      //   ns.version = ans.size();
      //   ns.value = (lli)a[ns.u] * (ns.version);
      //   ns.above = sum_to_root[ns.u] * (ns.version);
      // }
      // std::sort(pq.begin(), pq.end());
      const State s = pq.top();
      pq.pop();
      ans.push_back(s.u);

      for (const int v : tree[s.u]) {
        Enqueue(v);
      }
    }
    // std::reverse(ans.begin(), ans.end());
    return ans;
  }
  std::vector<int> FindBestOrder4() {
    std::vector<std::pair<int, int>> cost_nodes;
    cost_nodes.reserve(n);
    for (int i = 0; i < n; ++i) cost_nodes.emplace_back(a[i], i);
    std::sort(cost_nodes.begin(), cost_nodes.end());
    std::reverse(cost_nodes.begin(), cost_nodes.end());

    std::vector<bool> done(n, false);
    std::vector<int> ans;
    for (const auto [cost, i] : cost_nodes) {
      std::cout << "\t\t" << cost << " " << i << "\n";
      if (done[i]) continue;

      int u = i;
      std::stack<int> to_add;
      to_add.push(u);
      while (p[u] != -1 && !done[p[u]]) {
        u = p[u];
        to_add.push(u);
      }

      while (!to_add.empty()) {
        const int v = to_add.top();
        done[v] = true;
        ans.push_back(v);
        to_add.pop();
      }
    }
    return ans;
  }
  std::vector<int> FindBestOrder5() {
    std::vector<std::pair<int, int>> cost_nodes;
    cost_nodes.reserve(n);
    for (int i = 0; i < n; ++i) cost_nodes.emplace_back(a[i], i);
    std::sort(cost_nodes.begin(), cost_nodes.end());

    std::vector<bool> done(n, false);
    std::vector<int> ans;
    for (const auto [cost, i] : cost_nodes) {
      std::cout << "\t\t" << cost << " " << i << "\n";
      if (done[i]) continue;

      int u = i;
      std::queue<int> to_add;
      to_add.push(u);
      while (p[u] != -1 && !done[p[u]]) {
        u = p[u];
        to_add.push(u);
      }

      while (!to_add.empty()) {
        const int v = to_add.front();
        done[v] = true;
        ans.push_back(v);
        to_add.pop();
      }
    }
    std::reverse(ans.begin(), ans.end());
    return ans;
  }

  std::vector<int> FindBestOrder6() {
    std::vector<std::pair<int, int>> cost_nodes;
    cost_nodes.reserve(n);
    for (int i = 0; i < n; ++i) cost_nodes.emplace_back(a[i], i);
    std::sort(cost_nodes.begin(), cost_nodes.end());
    std::reverse(cost_nodes.begin(), cost_nodes.end());

    std::vector<bool> done(n, false);
    std::map<int, std::list<int>::iterator> it_by_node;
    std::list<int> ans;
    auto Add = [&](std::list<int>::iterator nxt, const int u) {
      const int pos = std::distance(ans.begin(), nxt) - 1;
      done[u] = true;
      it_by_node[u] = ans.insert(nxt, u);
    };
    auto GetValue = [&](std::list<int>::iterator nxt, const int u) {
      std::list<int>::iterator start = ans.begin();
      lli value = 0;
      int pos = std::distance(ans.begin(), start);
      while (start != ans.end()) {
        if (std::next(start) == nxt) {
          value += (lli)a[*start] * pos;
          ++pos;
          value += (lli)a[u] * pos;
        } else {
          value += (lli)a[*start] * pos;
        }
        ++pos, ++start;
      }
      return value;
    };

    for (const auto [cost, i] : cost_nodes) {
      if (done[i]) continue;

      int u = i;
      std::stack<int> to_add;
      to_add.push(u);
      while (p[u] != -1 && !done[p[u]]) {
        u = p[u];
        to_add.push(u);
      }

      while (!to_add.empty()) {
        const int v = to_add.top();
        to_add.pop();

        if (p[v] != -1 && done[p[v]]) {
          const auto start = std::next(it_by_node[p[v]]);
          auto curr = start;
          auto best_it = curr;
          lli best_value = GetValue(curr, v);
          while (curr != ans.end()) {
            ++curr;
            const lli value = GetValue(curr, v);
            if (value < best_value) {
              best_it = curr, best_value = value;
            }
          }
          Add(best_it, v);
        } else {
          Add(ans.end(), v);
        }
      }
    }
    return std::vector<int>(ans.begin(), ans.end());
  }

  std::pair<lli, std::vector<int>> FindBestOrder7(const int i,
                                                  std::vector<bool> done) {
    // std::cout << "\t" << i << " ";
    // for (const int d : done) std::cout << d;
    // std::cout << "\n";
    if (i == n) {
      return std::make_pair(0LL, std::vector<int>{});
    }

    std::pair<lli, std::vector<int>> ans(1e9, {});

    for (int j = 0; j < n; ++j) {
      if (done[j]) continue;
      if (p[j] != -1 && !done[p[j]]) continue;

      done[j] = true;
      auto curr = FindBestOrder7(i + 1, done);
      done[j] = false;
      curr.first += (lli)i * a[j];
      curr.second.push_back(j);
      ans = std::min(ans, curr);
    }

    return ans;
  }

  lli ComputeExpectedOperations(const std::vector<int>& order) {
    DEBUG {
      std::cout << "\t";
      for (int i = 0; i < order.size(); ++i) {
        std::cout << order[i] << " ";
      }
      std::cout << "\n";
    }
    std::fflush(stdout);
    assert(order.size() == n);
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

    tree.resize(n), requirements.resize(n, 0);
    for (int i = 1; i < n; ++i) {
      tree[p[i]].push_back(i);
      ++requirements[p[i]];
    }

    DEBUG PrintTree();

    sum_to_root.resize(n);
    FillSumToRoot();
    std::vector<int> best_order =
        FindBestOrder7(0, std::vector<bool>(n, false)).second;
    std::reverse(best_order.begin(), best_order.end());
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
