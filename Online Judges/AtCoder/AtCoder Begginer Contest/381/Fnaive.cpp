#include <bits/stdc++.h>
#define DEBUG if (0)
#define lli long long int
#define ldouble long double

const int kMaxA = 20;

struct TestCase {
  int n;
  std::vector<int> a, a_mask;
  std::vector<std::vector<int>> nxt;

  std::vector<std::vector<int>> memo;
  int Solve(const int i = 0, const int mask = 0, const int latest = kMaxA) {
    if (i == n) {
      return 0;
    }
    DEBUG std::cout << "\t\t" << i << " " << a[i] << " " << latest << " | "
                    << mask << "\n";
    // if (ans != -1) return ans;

    int ans = 0;
    for (int j = 0; j < kMaxA; ++j) {
      if (((1 << j) & mask) != 0) continue;
      if (nxt[j][i] == n || nxt[j][nxt[j][i] + 1] == n) continue;
      ans = std::max(ans,
                     Solve(nxt[j][nxt[j][i] + 1] + 1, mask | (1 << j), j) + 2);
    }

    return ans;
  }

  struct State {
    int i, mask, latest;
    bool operator<(const State& other) const {
      return std::__popcount(mask) > std::__popcount(other.mask) ||
             (std::__popcount(mask) == std::__popcount(other.mask) &&
              i < other.i);
    }
  };
  int Solve2() {
    std::queue<State> pq;
    pq.emplace(0, 0, kMaxA);
    int ans = 0;
    while (!pq.empty()) {
      State s = pq.front();
      pq.pop();
      const int i = s.i, mask = s.mask, latest = s.latest;
      ans = std::max(ans, 2 * std::__popcount(mask));
      if (i == n) {
        continue;
      }
      int& curr = memo[latest][mask];
      if (curr != -1 && i >= curr) continue;
      curr = i;
      // std::cout << i << " " << mask << " " << latest << "\n";

      for (int j = 0; j < kMaxA; ++j) {
        if (((1 << j) & mask) != 0) continue;
        if (nxt[j][i] == n || nxt[j][nxt[j][i] + 1] == n) continue;
        pq.emplace(nxt[j][nxt[j][i] + 1] + 1, mask | (1 << j), j);
      }
    }
    return ans;
  }

  bool Run() {
    if (!(std::cin >> n)) return false;
    a.resize(n);
    for (int& ai : a) {
      std::cin >> ai;
      --ai;
    }

    nxt.resize(kMaxA, std::vector<int>(n + 1, n));
    for (int i = n - 1; i >= 0; --i) {
      for (int j = 0; j < kMaxA; ++j) nxt[j][i] = nxt[j][i + 1];
      nxt[a[i]][i] = i;
    }

    // memo.resize(kMaxA + 1, std::vector<int>(1 << kMaxA, -1));
    int ans = Solve();
    std::cout << ans << "\n";

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
