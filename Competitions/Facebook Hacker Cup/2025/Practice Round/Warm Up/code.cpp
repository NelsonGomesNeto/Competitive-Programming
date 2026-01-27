#include <bits/stdc++.h>
#define DEBUG if (0)
#define lli long long int
#define ldouble long double

int N;
struct TestCase {
  struct Dish {
    int start, target, idx;
    auto operator<=>(const Dish& other) const {
      return start == other.start ? target <=> other.target
                                  : start <=> other.start;
    }
  };
  std::vector<Dish> dishes;
  std::multiset<std::pair<int, int>> available;
  bool Run() {
    if (!(std::cin >> N)) return false;
    dishes.resize(N);
    for (int i = 0; i < N; ++i) std::cin >> dishes[i].start;
    for (int i = 0; i < N; ++i) {
      std::cin >> dishes[i].target;
      dishes[i].idx = i;
      available.emplace(dishes[i].start, i);
    }
    std::sort(dishes.begin(), dishes.end());

    bool possible = true;
    std::vector<std::pair<int, int>> ans;
    for (int i = 0; i < N; ++i) {
      const auto& [start, target, idx] = dishes[i];
      if (start == target) continue;
      if (start > target) {
        possible = false;
        break;
      }
      const auto it = available.lower_bound({target, 0});
      if (it == available.end()) {
        possible = false;
        break;
      }
      available.erase(available.find({start, idx}));

      ans.emplace_back(it->second, idx);
    }

    if (!possible) {
      std::cout << "-1\n";
    } else {
      std::cout << ans.size() << "\n";
      for (int i = 0; i < (int)ans.size(); ++i) {
        const auto [a, b] = ans[i];
        std::cout << (a + 1) << " " << (b + 1) << "\n";
      }
    }

    return true;
  }
};
TestCase test_case;

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int test_cases;
  std::cin >> test_cases;
  for (int t = 1; t <= test_cases; ++t) {
    test_case = TestCase{};
    std::cout << "Case #" << t << ": ";
    test_case.Run();
  }

  return 0;
}
