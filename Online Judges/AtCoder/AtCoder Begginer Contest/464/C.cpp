#include <bits/stdc++.h>
#define DEBUG if (0)
#define lli long long int
#define ldouble long double

struct TestCase {
  int n, m;
  std::vector<std::vector<std::pair<int, int>>> updates;
  bool Run() {
    if (!(std::cin >> n >> m)) return false;
    updates.resize(m);
    std::map<int, int> cnt;
    for (int i = 0; i < n; ++i) {
      int a, d, b;
      std::cin >> a >> d >> b;
      --a, --b, --d;
      updates[d].emplace_back(a, b);
      cnt[a]++;
    }

    for (int i = 0; i < m; ++i) {
      for (const auto [a, b] : updates[i]) {
        if (a == b) continue;
        auto it = cnt.find(a);
        if (it->second == 1) cnt.erase(it);
        else it->second--;
        cnt[b]++;
      }
      DEBUG std::println("{}", cnt);
      std::println("{}", cnt.size());
    }

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
