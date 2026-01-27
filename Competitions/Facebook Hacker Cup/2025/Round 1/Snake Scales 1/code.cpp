#include <bits/stdc++.h>
#define DEBUG if (0)
#define lli long long int
#define ldouble long double

int N;
struct TestCase {
  std::vector<int> a;
  bool Run() {
    if (!(std::cin >> N)) return false;
    a.resize(N);
    for (auto& ai : a) std::cin >> ai;

    int ans = 0;
    for (int i = 1; i < N; ++i) {
      ans = std::max(ans, std::abs(a[i] - a[i - 1]));
    }
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
    std::cout << "Case #" << t << ": ";
    test_case.Run();
  }

  return 0;
}
