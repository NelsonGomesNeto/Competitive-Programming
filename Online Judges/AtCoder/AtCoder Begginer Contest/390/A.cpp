#include <bits/stdc++.h>
#define DEBUG if (0)
#define lli long long int
#define ldouble long double

struct TestCase {
  std::vector<int> a, b;
  bool Run() {
    a.resize(5);
    if (!(std::cin >> a[0])) return false;
    for (int i = 1; i < 5; ++i) std::cin >> a[i];
    b = a;
    std::ranges::sort(a);

    bool can = !(b == a);
    for (int i = 1; i < 5; ++i) {
      if (b[i] < b[i - 1]) {
        std::swap(b[i], b[i - 1]);
        break;
      }
    }

    can &= a == b;
    std::cout << (can ? "Yes" : "No") << "\n";

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
