#include <bits/stdc++.h>
#define DEBUG if (0)
#define lli long long int
#define ldouble long double

lli ModExp(lli x, lli y, const lli mod) {
  lli ans = 1;
  while (y) {
    if (y & 1) ans = ans * x % mod;
    x = x * x % mod, y >>= 1;
  }
  return ans;
}

struct TestCase {
  int n;
  lli k;
  std::vector<int> p, ans;

  std::vector<std::pair<int, int>> cycle_map;
  std::vector<std::vector<int>> cycles;

  bool Run() {
    if (!(std::cin >> n >> k)) return false;
    p.resize(n);
    for (int& pi : p) {
      std::cin >> pi;
      --pi;
    }

    cycle_map.resize(n, {-1, -1});
    for (const int pi : p) {
      int u = pi;
      if (cycle_map[u].first != -1) continue;

      std::vector<int> cycle;
      cycle_map[u] = {cycles.size(), cycle.size()};
      cycle.push_back(u);
      u = p[u];
      while (u != pi) {
        cycle_map[u] = {cycles.size(), cycle.size()};
        cycle.push_back(u);
        u = p[u];
      }
      cycles.push_back(cycle);
    }

    DEBUG {
      for (const auto& cycle : cycles) {
        std::cout << "\t";
        for (const int pi : cycle) std::cout << (pi + 1) << " ";
        std::cout << "\n";
      }
    }

    ans = p;
    for (int& pi : ans) {
      const auto& cycle = cycles[cycle_map[pi].first];
      // sum 2^i, i = [0 : k - 1]
      // delta = 2^k - 1
      const int new_pos =
          ((cycle_map[pi].second + ModExp(2, k, cycle.size()) - 1) %
               cycle.size() +
           cycle.size()) %
          cycle.size();

      pi = cycle[new_pos];
    }

    for (int i = 0; i < n; ++i) {
      std::cout << (ans[i] + 1) << (i + 1 == n ? '\n' : ' ');
    }

    DEBUG { std::cout << "---------------------\n"; }

    return true;
  }
};
TestCase test_case;

int main() {
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
