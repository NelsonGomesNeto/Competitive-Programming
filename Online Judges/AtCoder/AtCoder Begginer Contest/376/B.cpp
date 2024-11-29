#include <bits/stdc++.h>
#define DEBUG if (0)
#define lli long long int
#define ldouble long double

struct TestCase {
  int n, q;
  std::vector<std::pair<char, int>> queries;

  int Move(const int from, const int to, const int block) {
    auto MoveUntilFinish = [&](const int delta) {
      int operations = 0, curr = from;
      while (curr != to) {
        curr += delta;
        if (curr > n) curr = 1;
        if (curr < 1) curr = n;
        if (curr == block) return std::numeric_limits<int>::max();
        ++operations;
      }
      return operations;
    };
    return std::min(MoveUntilFinish(-1), MoveUntilFinish(1));
  }

  bool Solve() {
    if (!(std::cin >> n >> q)) return false;
    queries.resize(q);
    for (auto& [h, t] : queries) std::cin >> h >> t;

    int ans = 0;
    int l = 1, r = 2;
    for (const auto [h, t] : queries) {
      if (h == 'L') {
        ans += Move(l, t, r);
        l = t;
      } else {
        ans += Move(r, t, l);
        r = t;
      }
    }
    std::cout << ans << "\n";

    return true;
  }
};
TestCase test_case;

int main() {
  do {
    test_case = TestCase{};
  } while (test_case.Solve());
  return 0;
}
