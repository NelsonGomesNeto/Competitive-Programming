#include <bits/stdc++.h>
#define DEBUG if (0)
#define lli long long int
#define ldouble long double

const lli kMod = 998244353LL;

int N;
std::string T;
struct TestCase {
  bool Get(const lli mask, const int i) { return mask & (1LL << i); }
  lli Set(const lli mask, const int i) { return mask | (1LL << i); }

  std::vector<std::vector<lli>> memo;
  lli Solve(const int l = 0, const lli mask = 0) {
    if (l == N) {
      return 1;
    }
    lli& ans = memo[l][mask];
    if (ans != -1) return ans;

    ans = 0;
    for (int i = 0; i < N; ++i) {
      if (Get(mask, i)) continue;

      int j = i;
      while (j + 1 < N && (Get(mask, j + 1) || T[i] == T[j + 1])) ++j;
      ans = (ans + Solve(l + 1, Set(mask, i))) % kMod;

      i = j;
    }

    return ans;
  }

  bool Run() {
    if (!(std::cin >> N >> T)) return false;

    if (N == 1) {
      std::cout << "1\n";
      return true;
    }

    memo.resize(N, std::vector<lli>(1LL << N, -1));
    const lli ans = Solve();
    std::cout << ans << "\n";

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
