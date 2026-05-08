#include <bits/stdc++.h>
#define DEBUG if (0)
#define DEBUG2 if (0)
#define lli long long int
#define ldouble long double

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
    if (cnt < k) return -1e6;
    return sum;
  }

  std::vector<int> below;
  std::vector<std::vector<std::pair<int, int>>> belows;
  int Dfs(const int u, const int prv = -1) {
    for (const auto v : tree[u]) {
      if (v == prv) continue;
      belows[u].push_back(std::make_pair(Dfs(v, u), v));
    }
    std::sort(belows[u].begin(), belows[u].end(),
              std::greater<std::pair<int, int>>());

    below[u] = 1;
    if (tree[u].size() >= 4) {
      below[u] += FilterAndSum(belows[u], -1, (prv == -1 ? 4 : 3));
    } else if (prv == -1) {
      below[u] += belows[u][0].first;
    }

    DEBUG2 std::cout << "\t" << u << " -> " << below[u] << "\n";

    return below[u];
  }

  int Naive() {
    int ans = 0;
    for (int i = 0; i < n; ++i) {
      std::fill(below.begin(), below.end(), 0);
      std::fill(belows.begin(), belows.end(), std::vector<std::pair<int, int>>{});
      const int res = Dfs(i);
      ans = std::max(ans, res);
      // break;
    }
    return ans;
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
    below.resize(n);
    belows.resize(n, {});

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

    std::cout << Naive() << "\n";

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
