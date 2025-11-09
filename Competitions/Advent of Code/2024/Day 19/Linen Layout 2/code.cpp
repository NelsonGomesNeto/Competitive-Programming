#include <bits/stdc++.h>
#define DEBUG if (0)
#define lli long long int
#define ldouble long double

struct Problem {
  std::vector<std::string> towels;
  std::vector<std::string> designs;

  std::vector<lli> memo;
  lli FindAllWays(const std::string& design, const int i) {
    if (i == design.size()) {
      return 1;
    }
    lli& ans = memo[i];
    if (ans != -1) return ans;

    ans = 0;
    for (const auto& t : towels) {
      if (i + (int)t.size() > (int)design.size()) continue;
      if (design.substr(i, t.size()) != t) continue;
      ans += FindAllWays(design, i + t.size());
    }
    return ans;
  }
  lli FindAllWays(const std::string& design) {
    memo.resize(design.size());
    std::ranges::fill(memo, -1);
    return FindAllWays(design, 0);
  }

  void Solve() {
    std::string line;
    std::getline(std::cin, line);
    std::istringstream sin(line);
    for (std::string towel; std::getline(sin, towel, ',');) {
      towels.push_back(towel);
      sin.ignore(1);
    }
    std::cout << "towels:\n";
    for (const auto& t : towels) {
      std::cout << "\t" << t << "\n";
    }

    std::getline(std::cin, line);
    for (; std::getline(std::cin, line);) {
      designs.push_back(line);
    }
    std::cout << "designs:\n";
    for (const auto& d : designs) {
      std::cout << "\t" << d << "\n";
    }

    lli ans = 0;
    for (const auto& d : designs) {
      const lli all_ways = FindAllWays(d);
      std::cout << d << " | " << all_ways << "\n";
      ans += all_ways;
    }
    std::println("ans: {}", ans);
  }
};
Problem problem;

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  problem.Solve();

  return 0;
}
