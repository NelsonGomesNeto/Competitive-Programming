#include <bits/stdc++.h>
#define DEBUG if (0)
#define lli long long int
#define ldouble long double

// 1e5 sacos com 1e4 pipocas para 1 competidor a 1 pipoca/s.
const int kMaxAns = 1e9;

struct TestCase {
  int n, c, t;
  std::vector<int> p;

  int Can(const int x) {
    for (int i = 0, competitor = 0, sum = 0; i < n; ++i) {
      while (std::ceil((double)(sum + p[i]) / t) > x) {
        ++competitor, sum = 0;
        if (competitor == c) return false;
      }
      sum += p[i];
    }
    return true;
  }

  int BinarySearch(int lo, int hi) {
    while (lo < hi) {
      const int mid = lo + ((hi - lo) >> 1);
      if (Can(mid)) hi = mid;
      else lo = mid + 1;
    }
    return lo;
  }

  bool Run() {
    if (!(std::cin >> n >> c >> t)) return false;
    p.resize(n);
    for (auto& pi : p) std::cin >> pi;

    const int ans = BinarySearch(/*lo=*/1, /*hi=*/kMaxAns);
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
