#include <bits/stdc++.h>
#define DEBUG if (0)
#define lli long long int
#define ldouble long double

struct TestCase {
  int n;
  std::vector<std::vector<int>> tree;
  std::vector<int> a;
  std::string ans;

  void Update(int u, int v, int w) {
    std::unordered_map<int, int> cnt;
    ++cnt[a[u]];
    ++cnt[a[v]];
    ++cnt[a[w]];
    for (const auto& [value, c] : cnt) {
      if (c >= 2) {
        ans[value] = '1';
      }
    }
  }
  void Dfs(int u = 0, int prv = -1, int prv2 = -1) {
    if (prv != -1 && prv2 != -1) {
      Update(u, prv, prv2);
    }

    for (const auto& v : tree[u]) {
      if (v == prv) continue;
      Dfs(v, u, prv);
    }
  }

  bool Run() {
    if (!(std::cin >> n)) return false;
    a.resize(n);
    for (auto &ai : a) {
      std::cin >> ai;
      --ai;
    }
    tree.resize(n, {});
    for (int i = 1; i < n; ++i) {
      int u, v;
      std::cin >> u >> v;
      --u, --v;
      tree[u].push_back(v);
      tree[v].push_back(u);
    }

    ans.resize(n, '0');
    for (int i = 0; i < n; ++i) {
      std::unordered_map<int, int> curr;
      ++curr[a[i]];
      for (const int v : tree[i]) {
        ++curr[a[v]];
      }

      for (const int v : tree[i]) {
        if (curr[a[v]] <= 1) continue;
        ans[a[v]] = '1';
      }
    }
    Dfs();

    std::cout << ans << "\n";

    return true;
  }
};
TestCase test_case;

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int test_cases;
  std::cin >> test_cases;
  for (int t = 1; t <= test_cases; ++t) {
    test_case = TestCase{};
    test_case.Run();
  }

  return 0;
}
