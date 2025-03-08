#include <bits/stdc++.h>
#define DEBUG if (0)
#define lli long long int
#define ldouble long double

const lli kMod = 998244353;

struct TestCase {
  int n, m;
  std::vector<int> a;
  std::vector<int> i_to_cycle;
  std::vector<std::vector<int>> rev;

  std::vector<std::vector<lli>> memo;
  lli Solve(int i, int prv) {
    lli& ans = memo[i][prv];
    if (ans != -1) return ans;

    ans = 0;
    for (int j = 1; j <= prv; ++j) {
      lli res = 1;
      for (const int v : rev[i]) res = (res * Solve(v, j)) % kMod;
      ans = (ans + res) % kMod;
    }
    return ans;
  }
  lli Solve() {
    memo.clear();
    memo.resize(n, std::vector<lli>(m + 1, -1));

    lli ans = 1;
    for (int i = 0; i < n; ++i) {
      // for (int i = n - 1; i >= 0; --i) {
      if (i_to_cycle[i] == -1 || memo[i_to_cycle[i]][m] != -1) continue;
      const lli res = Solve(i, m);
      DEBUG std::cout << std::format("\tres | {}: {}\n", i, res);
      if (res == 0) continue;
      ans = (ans * res) % kMod;
    }
    return ans;
  }

  void BuildRev() {
    rev.resize(n);
    std::ranges::fill(rev, std::vector<int>{});
    // x_i <= x_ai
    // x_ai >= x_i
    for (int i = 0; i < n; ++i) rev[a[i]].push_back(i);

    DEBUG {
      PrintRev();
      std::cout << "-------\n";
    }

    std::vector<bool> visited(n);
    i_to_cycle.resize(n);
    std::ranges::fill(i_to_cycle, -1);
    for (int i = 0; i < n; ++i) {
      if (rev[i].empty() || i_to_cycle[i] != -1) continue;

      const bool is_self_cycle = [&]() {
        std::ranges::fill(visited, false);
        int u = i;
        for (; !visited[u]; u = a[u]) {
          visited[u] = true;
        }
        return u == i;
      }();

      if (!is_self_cycle) continue;

      i_to_cycle[i] = i;
      std::set<int> new_childs(rev[i].begin(), rev[i].end());
      for (int v = a[i]; v != i; v = a[v]) {
        for (const int c : rev[v]) new_childs.insert(c);
        i_to_cycle[v] = i;
      }
      rev[i].clear();
      for (const int c : new_childs) {
        if (i_to_cycle[c] == i) continue;
        rev[i].push_back(c);
      }
      for (int v = a[i]; v != i; v = a[v]) rev[v].clear();
    }
  }

  void PrintRev() {
    for (int i = 0; i < n; ++i) {
      std::cout << "\t" << i << ":";
      for (const int v : rev[i]) std::cout << " " << v;
      std::cout << "\n";
    }
  }

  bool Run() {
    if (!(std::cin >> n >> m)) return false;
    a.resize(n);
    for (int& ai : a) {
      std::cin >> ai;
      --ai;
    }

    BuildRev();

    DEBUG { PrintRev(); }

    lli ans = Solve();
    std::cout << ans << "\n";

    return true;
  }
};
TestCase test_case;

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  do {
    test_case = TestCase{};
  } while (test_case.Run());

  return 0;
}
