#include <bits/stdc++.h>
#define DEBUG if (0)
#define lli long long int
#define ldouble long double

struct TestCase {
  int n;
  struct Skill {
    int a, b;
  };
  std::vector<Skill> skills;
  std::vector<std::vector<int>> pos_by_skill;
  std::vector<bool> learned;
  void Learn(const int x) {
    if (learned[x]) return;
    learned[x] = true;
    for (const int i : pos_by_skill[x]) {
      Learn(i + 1);
    }
  }
  bool Run() {
    if (!(std::cin >> n)) return false;
    skills.resize(n);
    pos_by_skill.resize(n + 1, std::vector<int>{});
    for (int i = 0; i < n; ++i) {
      auto& [a, b] = skills[i];
      std::cin >> a >> b;
      pos_by_skill[a].push_back(i);
      if (b != a) pos_by_skill[b].push_back(i);
    }

    learned.resize(n + 1, false);
    for (int i = 0; i < (int)skills.size(); ++i) {
      const auto [a, b] = skills[i];
      if ((a == 0 && b == 0) || (learned[a] || learned[b])) Learn(i + 1);
    }
    int ans = 0;
    for (const bool l : learned) ans += l;
    std::cout << ans << "\n";

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
