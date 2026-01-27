#include <bits/stdc++.h>
#define DEBUG if (0)
#define lli long long int
#define ldouble long double

struct TestCase {
  int n;
  std::vector<int> a;
  bool Run() {
    if (!(std::cin >> n)) return false;
    a.resize(n);
    for (auto& ai : a) std::cin >> ai;

    std::list<int> curr(a.begin(), a.end());
    for (auto it = curr.begin(); it != curr.end();) {
      auto jt = std::next(it);
      if (jt == curr.end()) break;
      auto kt = std::next(jt);
      if (kt == curr.end()) break;
      auto lt = std::next(kt);
      if (lt == curr.end()) break;

      if (*jt != *it || *kt != *it || *lt != *it) {
        ++it;
        continue;
      }

      curr.erase(lt);
      curr.erase(kt);
      curr.erase(jt);
      it = curr.erase(it);

      for (int j = 0; j < 3; ++j) {
        it = std::prev(it);
        if (it == curr.end()) {
          it = curr.begin();
          break;
        }
      }
    }

    std::println("{}", curr.size());

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
