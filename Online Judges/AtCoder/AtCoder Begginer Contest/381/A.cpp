#include <bits/stdc++.h>
#define DEBUG if (0)
#define lli long long int
#define ldouble long double

const std::string kYes = "Yes", kNo = "No";

struct TestCase {
  int n;
  std::string s;
  std::string Solve() {
    if (s[0] == '/') {
      if (n == 1)
        return kYes;
      else
        return kNo;
    }

    if (s[0] != '1') return kNo;

    int one_size = 1;
    int i = 0;
    while (i + 1 < n && s[i + 1] == '1') ++i, ++one_size;

    ++i;
    if (i >= n || s[i] != '/') return kNo;

    ++i;
    if (i >= n || s[i] != '2') return kNo;
    int two_size = 1;
    while (i + 1 < n && s[i + 1] == '2') ++i, ++two_size;

    DEBUG std::cout << i << " " << one_size << " " << two_size << "\n";

    return i == n - 1 && one_size == two_size ? kYes : kNo;
  }
  bool Run() {
    if (!(std::cin >> n)) return false;
    std::cin >> s;

    std::cout << Solve() << "\n";

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
