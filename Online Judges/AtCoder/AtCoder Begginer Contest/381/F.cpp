#include <bits/stdc++.h>
#define DEBUG if (0)
#define lli long long int
#define ldouble long double

const int kMaxA = 20;

std::string Picks(int mask) {
  std::ostringstream sout;
  bool first = true;
  for (int i = 0; mask; ++i, mask >>= 1) {
    if (~mask & 1) continue;
    if (!first) sout << " ";
    first = false;
    sout << (i + 1);
  }
  return sout.str();
}

struct TestCase {
  int n;
  std::vector<int> a, a_mask;
  std::vector<std::vector<int>> nxt;
  int max_a;

  std::vector<std::pair<short, int>> memo;
  short Solve(const int i = 0, const int mask = 0, const int latest = kMaxA) {
    if (i == n) {
      return 0;
    }
    DEBUG {
      for (int j = 0, end = std::__popcount(mask); j <= end; ++j)
        std::cout << "\t";
      std::cout << "i: " << i << " ai: " << (a[i] + 1) << " l: " << (latest + 1)
                << " | mask: " << mask << " | " << Picks(mask) << "\n";
    }
    auto& [ans, pos] = memo[mask];
    if (ans != -1 && pos <= i) return ans;
    pos = i;

    ans = 0;
    for (int j = 0; j < kMaxA; ++j) {
      if (((1 << j) & mask) != 0 || nxt[j][nxt[j][i] + 1] == n) continue;
      short res = Solve(nxt[j][nxt[j][i] + 1] + 1, mask | (1 << j), j) + 2;
      ans = std::max(ans, res);
    }

    return ans;
  }

  std::vector<int> memo2;
  int Solve2() {
    memo2.resize(1 << kMaxA, n);
    memo2[0] = -1;
    int ans = 0;
    for (int mask = 0, end = 1 << kMaxA; mask < end; ++mask) {
      int& res = memo2[mask];
      for (int j = 0; j < kMaxA; ++j) {
        if (~mask & (1 << j)) continue;
        res = std::min(res, nxt[j][nxt[j][memo2[mask ^ (1 << j)] + 1] + 1]);
      }
      if (res >= n) continue;
      ans = std::max(ans, 2 * std::__popcount(mask));
    }
    return ans;
  }

  std::vector<int> memo3;
  int Solve3(int mask) {
    if (mask == 0) {
      return -1;
    }
    int& ans = memo3[mask];
    if (ans != -2) return ans;

    ans = n;
    for (int j = 0; j < kMaxA; ++j) {
      if (~mask & (1 << j)) continue;
      ans = std::min(ans, nxt[j][nxt[j][Solve3(mask ^ (1 << j)) + 1] + 1]);
    }

    return ans;
  }

  /*
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
      const int curr = memo[latest][mask];
      if (curr != -1 && i > curr) continue;
      // std::cout << i << " " << mask << " " << latest << "\n";

      // bool added = false;
      for (int j = 0; j < kMaxA; ++j) {
        if (((1 << j) & mask) != 0 || nxt[j][nxt[j][i] + 1] == n) continue;
        const int nxt_pos = nxt[j][nxt[j][i] + 1] + 1;
        int& nxt_state = memo[j][mask | (1 << j)];
        if (nxt_state != -1 && nxt_state < nxt_pos) continue;
        nxt_state = nxt_pos;
        pq.emplace(nxt_pos, mask | (1 << j), j);
        // added = true;
      }
      // if (!added) break;
    }
    return ans;
  }
  */

  bool Run() {
    if (!(std::cin >> n)) return false;
    // kMaxA = 0;
    a.resize(n);
    for (int& ai : a) {
      std::cin >> ai;
      --ai;
      // kMaxA = std::max(kMaxA, ai);
    }
    // ++kMaxA;

    nxt.resize(kMaxA, std::vector<int>(n + 2, n));
    for (int i = n - 1; i >= 0; --i) {
      for (int j = 0; j < kMaxA; ++j) nxt[j][i] = nxt[j][i + 1];
      nxt[a[i]][i] = i;
    }

    // memo.resize(1 << kMaxA, std::make_pair(-1, -1));
    // int ans = Solve();
    // int ans = Solve2();
    memo3.resize(1 << kMaxA, -2);
    int ans = 0;
    for (int mask = (1 << kMaxA) - 1; mask >= 0; --mask) {
      int best_pos = Solve3(mask);
      if (best_pos >= n) continue;
      ans = std::max(ans, 2 * std::__popcount(mask));
    }
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
