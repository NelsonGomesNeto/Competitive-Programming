#include <bits/stdc++.h>
#define DEBUG if (0)
#define lli long long int
#define ldouble long double

struct TestCase {
  std::vector<std::string> table;

  void Fill(int i, int j) {
    for (int jj = 0; jj < 8; ++jj)
      table[i][jj] = table[i][jj] == '#' ? '#' : 'O';
    for (int ii = 0; ii < 8; ++ii)
      table[ii][j] = table[ii][j] == '#' ? '#' : 'O';
  }

  bool Run() {
    table.resize(8);
    if (!(std::cin >> table[0])) return false;
    for (int i = 1; i < 8; ++i) std::cin >> table[i];

    for (int i = 0; i < 8; ++i)
      for (int j = 0; j < 8; ++j) {
        if (table[i][j] != '#') continue;
        Fill(i, j);
      }

    int ans = 0;
    for (int i = 0; i < 8; ++i)
      for (int j = 0; j < 8; ++j) ans += table[i][j] == '.';
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
