#include <bits/stdc++.h>
#define DEBUG if (0)
#define DEBUG2 if (0)
#define lli long long int
#define ldouble long double

const int kInf = 1e6;

struct TestCase {
  int n;
  std::vector<std::vector<int>> tree;

  void PrintTree(const int u, const int prv = -1, const int depth = 1) {
    std::cout << std::string(2 * depth, ' ') << u << "\n";
    for (const auto v : tree[u]) {
      if (v == prv) continue;
      PrintTree(v, u, depth + 1);
    }
  }

  int FilterAndSum(const std::vector<std::pair<int, int>>& elements,
                   const int blocked, const int k) {
    int sum = 0, cnt = 0;
    for (const auto& [value, id] : elements) {
      if (id == blocked) continue;
      sum += value;
      if (++cnt == k) break;
    }
    if (cnt < k) return -kInf;
    return sum;
  }

  std::vector<std::vector<std::pair<int, int>>> belows;
  int Dfs(const int u, const int prv = -1) {
    for (const auto v : tree[u]) {
      if (v == prv) continue;
      belows[u].push_back(std::make_pair(Dfs(v, u), v));
    }
    std::sort(belows[u].begin(), belows[u].end(),
              std::greater<std::pair<int, int>>());

    int ans = 1;
    if (tree[u].size() >= 4) {
      // If possible, try to pick all children
      ans += FilterAndSum(belows[u], -1, (prv == -1 ? 4 : 3));
    } else if (prv == -1) {
      // If not AND is root: you may pick the best child
      ans += FilterAndSum(belows[u], -1, 1);
    }

    DEBUG2 std::cout << "\t" << u << " -> " << ans << "\n";

    return ans;
  }

  std::vector<int> ans, above;
  void Reroot(const int u, const int prv = -1) {
    // reroot
    if (prv != -1) {
      ans[u] = std::max({// pick 4 - all children
                         FilterAndSum(belows[u], -1, 4) + 1,
                         // pick 4 - 3 children + parent
                         FilterAndSum(belows[u], -1, 3) + above[prv] + 1,
                         // pick 1 - only parent
                         above[prv] + 1,
                         // pick 1 - best children
                         FilterAndSum(belows[u], -1, 1) + 1});
    }

    for (const auto v : tree[u]) {
      if (v == prv) continue;

      // update `above`
      // There are 3 cases (in order):
      // 1. Is leaf
      // 2. Pick 3 other children
      // 3. Pick 2 other children + parent
      above[u] = std::max(1, FilterAndSum(belows[u], v, 3) + 1);
      if (prv != -1)
        above[u] =
            std::max(above[u], FilterAndSum(belows[u], v, 2) + above[prv] + 1);

      Reroot(v, u);
    }
  }

  void Naive() {
    for (int i = 0; i < n; ++i) {
      const int ans = Dfs(i);
      std::cout << i << ": " << ans << "\n";
    }
  }

  bool Run() {
    if (!(std::cin >> n)) return false;
    tree.resize(n, {});
    for (int i = 1; i < n; ++i) {
      int u, v;
      std::cin >> u >> v;
      --u, --v;
      tree[u].push_back(v);
      tree[v].push_back(u);
    }

    DEBUG {
      PrintTree(0);
      Naive();
    }

    bool possible = false;
    for (int i = 0; i < n; ++i) {
      if (tree[i].size() >= 4) {
        possible = true;
        break;
      }
    }
    if (!possible) {
      std::cout << "-1\n";
      return true;
    }

    belows.resize(n, {});
    ans.resize(n);
    above.resize(n);
    ans[0] = Dfs(0);
    Reroot(0);
    std::cout << *std::max_element(ans.begin(), ans.end()) << "\n";

    return true;
  }
};
TestCase test_case;

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  // int test_cases;
  // std::cin >> test_cases;
  // for (int t = 1; t <= test_cases; ++t) {
  //   test_case = TestCase{};
  //   test_case.Run();
  // }

  do {
    test_case = TestCase{};
  } while (test_case.Run());

  return 0;
}
