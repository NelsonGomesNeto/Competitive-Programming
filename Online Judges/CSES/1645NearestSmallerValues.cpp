#include <bits/stdc++.h>
#define DEBUG if (0)
#define lli long long int
#define ldouble long double

struct TestCase {
  int n;
  std::vector<int> a;

  struct PosValue {
    int pos, value;
  };

  bool Run() {
    if (!(std::cin >> n)) return false;
    a.resize(n);
    for (int& ai : a) std::cin >> ai;

    std::vector<int> ans;
    ans.resize(n);
    std::stack<PosValue> s;
    for (const auto [i, ai] : a | std::views::enumerate) {
      while (!s.empty() && ai <= s.top().value) {
        s.pop();
      }
      if (s.empty())
        ans[i] = 0;
      else
        ans[i] = s.top().pos + 1;
      s.emplace(i, ai);
    }

    // std::cout << std::format("{}", ans | std::views::transform([](const int
    // v) {
    //                                  return std::to_string(v);
    //                                }) | std::views::join_with(' ') |
    //                                    std::ranges::to<std::string>());

    for (const auto [i, ansi] : ans | std::views::enumerate) {
      if (i) std::cout << " ";
      std::cout << ansi;
    }
    std::cout << "\n";

    // std::ostringstream sout;
    // for (const int ansi : ans) {
    //   if (!sout.str().empty()) sout << " ";
    //   sout << ansi;
    // }
    // std::cout << sout.str() << "\n";

    // std::println("{}", ans | std::views::transform([](const int v) {
    //                      return std::format("{}", v);
    //                    }) | std::views::join_with(' ') |
    //                        std::ranges::to<std::string>());

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
