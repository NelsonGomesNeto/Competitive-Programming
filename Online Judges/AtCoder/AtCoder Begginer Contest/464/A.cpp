#include <bits/stdc++.h>
#define DEBUG if (0)
#define lli long long int
#define ldouble long double

struct TestCase {
  std::string s;
  bool Run() {
    if (!(std::cin >> s)) return false;
    int e = 0, w = 0;
    for (const auto c : s) {
      e += c == 'E', w += c == 'W';
    }
    if (e > w) std::println("East");
    else std::println("West");
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
