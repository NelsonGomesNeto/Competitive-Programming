#include <bits/stdc++.h>
#define DEBUG if (0)
#define lli long long int
#define ldouble long double

struct TestCase {
  int n;
  struct Die {
    int k;
    std::vector<int> faces;
    std::unordered_map<int, int> cnt;
  };
  std::vector<Die> dice;

  int Count(const int i, const int x) {
    const auto& faces = dice[i].faces;
    auto loit = std::lower_bound(faces.begin(), faces.end(), x);
    if (loit == faces.end()) return 0;
    auto hiit = std::upper_bound(faces.begin(), faces.end(), x);
    return std::distance(loit, hiit);
  }

  bool Run() {
    if (!(std::cin >> n)) return false;
    dice.clear();
    dice.resize(n);
    for (auto& die : dice) {
      std::cin >> die.k;
      die.faces.resize(die.k);
      for (auto& f : die.faces) {
        std::cin >> f;
        ++die.cnt[f];
      }
      std::sort(die.faces.begin(), die.faces.end());
    }

    ldouble ans = 0;
    for (int i = 0; i < n; ++i) {
      for (int j = i + 1; j < n; ++j) {
        ldouble p = 0;
        for (const auto& [fi, cnt] : dice[i].cnt) {
          auto it = dice[j].cnt.find(fi);
          if (it == dice[j].cnt.end()) continue;
          p += ((ldouble)cnt / dice[i].k) * ((ldouble)it->second / dice[j].k);
        }
        ans = std::max(ans, p);
      }
    }
    std::cout << std::setprecision(15) << ans << "\n";

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
