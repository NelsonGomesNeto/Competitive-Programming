#include <bits/stdc++.h>
#define DEBUG if (0)
#define DEBUG2 if (0)
#define lli long long int
#define ldouble long double

const lli kMod = 998244353LL;

struct TestCase {
  int n, m;
  std::vector<int> a;
  std::vector<int> i_to_cycle;
  std::vector<std::vector<int>> rev;

  std::vector<int> FindSafeOrder() {
    std::vector<bool> usable(n, true);
    for (int i = 0; i < n; ++i) {
      if (i_to_cycle[i] != -1 && i_to_cycle[i] != i) {
        usable[i] = false;
      } else {
        for (const int v : rev[i]) usable[v] = false;
      }
    }
    std::vector<int> order;
    for (int i = 0; i < n; ++i) {
      if (!usable[i]) continue;
      order.push_back(i);
    }
    return order;
  }
  std::vector<int> FindSafeOrder2() {
    std::vector<int> original = FindSafeOrder(), order;
    std::reverse(original.begin(), original.end());
    std::queue<int> q(original.begin(), original.end());
    while (!q.empty()) {
      const int u = q.front();
      q.pop();
      order.push_back(u);

      for (const int v : rev[u]) {
        q.push(v);
      }
    }
    std::reverse(order.begin(), order.end());
    return order;
  }

  std::vector<std::vector<lli>> memo, pref;
  lli Pref(int i, int prv) {
    if (prv == 0) return 0;
    lli& ans = pref[i][prv];
    if (ans != -1) return ans;
    return ans = SolveTopDown(i, prv);
  }
  lli SolveTopDown(int i, int prv) {
    if (rev[i].empty()) return prv;
    lli& ans = memo[i][prv];
    if (ans != -1) return ans;

    ans = 1;
    for (const int v : rev[i]) ans = (ans * SolveTopDown(v, prv)) % kMod;
    ans = (ans + Pref(i, prv - 1)) % kMod;
    return ans;
  }
  lli SolveTopDown() {
    memo.clear();
    memo.resize(n, std::vector<lli>(m + 1, -1));
    pref = memo;

    const std::vector<int> order = FindSafeOrder();
    lli ans = 1;
    for (const int i : order) {
      const lli res = Pref(i, m);
      ans = (ans * res) % kMod;
      DEBUG2 std::cout << "\tcomputing: " << i << " | " << res << "\n";
    }
    return ans;
  }

  lli SolveTopDown2(int i, int prv) {
    if (prv == 0) return 0;
    if (rev[i].empty()) return prv;
    lli& ans = memo[i][prv];
    if (ans != -1) return ans;

    ans = 1;
    for (const int v : rev[i]) ans = (ans * SolveTopDown2(v, prv)) % kMod;
    ans = (ans + SolveTopDown2(i, prv - 1)) % kMod;
    return ans;
  }
  lli SolveTopDown2() {
    memo.clear();
    memo.resize(n, std::vector<lli>(m + 1, -1));

    const std::vector<int> order = FindSafeOrder();
    lli ans = 1;
    for (const int i : order) {
      const lli res = SolveTopDown2(i, m);
      ans = (ans * res) % kMod;
      DEBUG2 std::cout << "\tcomputing: " << i << " | " << res << "\n";
    }
    return ans;
  }

  // BottomUp \o/
  lli SolveBottomUp() {
    memo.clear();
    memo.resize(n, std::vector<lli>(m + 1, -1));

    const std::vector<int> order = FindSafeOrder2();

    for (int i = 0; i < n; i++) {
      if (!rev[i].empty()) continue;
      DEBUG2 std::cout << "\tcomputing: " << i << "\n";
      for (int prv = 1; prv <= m; ++prv) {
        memo[i][prv] = prv;
      }
    }

    // Originally, this was O(n*m*m). But can be easily optimized
    // to O(n*m) through prefix sums.
    for (const int i : order) {
      DEBUG2 std::cout << "\tcomputing: " << i << "\n";
      for (int prv = 1; prv <= m; ++prv) {
        lli& ans = memo[i][prv];
        // memo[i][prv] = sum(memo[i][1 : prv])
        ans = prv == 1 ? 0 : memo[i][prv - 1];
        // for (int j = 1; j <= prv; ++j) {
        lli res = 1;
        for (const int v : rev[i]) {
          assert(memo[v][prv] != -1);
          res = (res * memo[v][prv]) % kMod;
        }
        ans = (ans + res) % kMod;
        // }
      }
    }
    lli total = 1;
    for (const int i : FindSafeOrder()) {
      lli ans = memo[i][m];
      DEBUG2 std::cout << "\tcomputing2: " << i << " | " << ans << "\n";
      total = (total * ans) % kMod;
    }
    return total;
  }

  void BuildRev() {
    rev.resize(n);
    std::fill(rev.begin(), rev.end(), std::vector<int>{});
    // x_i <= x_ai
    // x_ai >= x_i
    for (int i = 0; i < n; ++i) rev[a[i]].push_back(i);

    DEBUG {
      PrintRev();
      std::cout << "-------\n";
    }

    std::vector<bool> visited(n);
    i_to_cycle.resize(n);
    std::fill(i_to_cycle.begin(), i_to_cycle.end(), -1);
    for (int i = 0; i < n; ++i) {
      if (rev[i].empty() || i_to_cycle[i] != -1) continue;

      const bool is_self_cycle = [&]() {
        std::fill(visited.begin(), visited.end(), false);
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
      std::cout << "\t" << i << " (" << rev[i].size() << "):";
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

    lli ans = SolveTopDown2();
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
