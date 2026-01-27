#include <bits/stdc++.h>
#define DEBUG if (0)
#define lli long long int
#define ldouble long double

int N, A, B;
struct TestCase {
  bool Run() {
    if (!(std::cin >> N >> A >> B)) return false;

    std::vector<int> divisors;
    for (int i = 2, curr = B; i <= curr; ++i) {
      while (curr % i == 0) curr /= i, divisors.push_back(i);
    }

    std::reverse(divisors.begin(), divisors.end());
    while ((int)divisors.size() < 2 * N) divisors.push_back(1);
    std::reverse(divisors.begin(), divisors.end());

    for (const auto d : divisors) std::cout << " " << d;
    std::cout << "\n";

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
    std::cout << "Case #" << t << ":";
    test_case.Run();
  }

  return 0;
}
