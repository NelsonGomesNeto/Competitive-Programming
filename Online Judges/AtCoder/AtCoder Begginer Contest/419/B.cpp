#include <bits/stdc++.h>
#define DEBUG if (0)
#define lli long long int
#define ldouble long double

struct TestCase {
  int q;
  std::multiset<int> bag;
  bool Run() {
    if (!(std::cin >> q)) return false;
    for (int qi = 0; qi < q; ++qi) {
      int op, x;
      std::cin >> op;
      if (op == 1) {
        std::cin >> x;
        bag.insert(x);
      } else {
        auto it = bag.begin();
        std::cout << *it << "\n";
        bag.erase(it);
      }
    }
    return true;
  }
};

int main() {
  while (true) {
    TestCase test_case{};
    if (!test_case.Run()) break;
  }
  return 0;
}