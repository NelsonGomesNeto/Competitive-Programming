#include <bits/stdc++.h>
#define DEBUG if (0)
#define lli long long int
#define ldouble long double

struct TestCase {
  std::vector<int> a;
  bool Run() {
    a.clear();
    a.resize(3);
    if (!(std::cin >> a[0] >> a[1] >> a[2])) return false;
    std::sort(a.begin(), a.end());

    bool can = false;
    do {
      if (a[0] * a[1] == a[2])
        can = true;
    } while (std::next_permutation(a.begin(), a.end()));

    std::cout << (can ? "Yes" : "No") << "\n";

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
