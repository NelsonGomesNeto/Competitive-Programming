#include <bits/stdc++.h>
#define DEBUG if (0)
#define lli long long int
#define ldouble long double

struct TestCase {
  int n, k, v;
  struct Candidate {
    int id;
    std::vector<int> votes;
    auto operator<=>(const Candidate& other) const {
      return votes == other.votes ? other.id <=> id : votes <=> other.votes;
    }
  };
  std::vector<Candidate> candidates;
  bool Run() {
    if (!(std::cin >> n >> k >> v)) return false;
    candidates.resize(k);
    for (auto [i, c] : candidates | std::views::enumerate) {
      c.id = i;
      c.votes.resize(v + 1, 0);
    }
    for (int i = 0; i < n; ++i) {
      int votes;
      std::cin >> votes;
      for (int j = 0; j < votes; ++j) {
        int candidate;
        std::cin >> candidate;
        if (j >= v) continue;
        --candidate;
        if (candidate < 0 || candidate >= k) continue;
        ++candidates[candidate].votes[j + 1];
        ++candidates[candidate].votes[0];
      }
    }

    std::ranges::sort(candidates, std::greater());
    std::vector<int> ans;
    for (int i = 0; i < k && (int)ans.size() < v; ++i) {
      int j = i;
      while (j + 1 < k && candidates[j + 1].votes == candidates[j].votes) ++j;
      for (int k = i; k <= j; ++k) ans.push_back(candidates[k].id);
      i = j;
    }
    std::println("{}", ans | std::views::transform([](const int i) {
                         return std::format("{}", i + 1);
                       }) | std::views::join_with(' ') |
                           std::ranges::to<std::string>());

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
    test_case.Run();
  }

  return 0;
}
