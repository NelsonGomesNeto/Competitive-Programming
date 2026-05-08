#include <bits/stdc++.h>
#define DEBUG if (0)
#define lli long long int
#define ldouble long double

std::vector<bool> is_open(256);
std::vector<char> closing(256);
struct TestCase {
  std::string seq;

  bool Run() {
    if (!(std::cin >> seq)) return false;

    bool balanced = true;
    std::stack<char> s;
    for (const auto c : seq) {
      if (is_open[c]) {
        s.push(c);
      } else if (!s.empty() && closing[s.top()] == c) {
        s.pop();
      } else {
        balanced = false;
      }
    }
    balanced &= s.empty();

    std::cout << (balanced ? "Yes" : "No") << "\n";

    return true;
  }
};
TestCase test_case;

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  is_open['('] = is_open['['] = is_open['<'] = true;
  closing['('] = ')';
  closing['['] = ']';
  closing['<'] = '>';

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
