#include <bits/stdc++.h>
#define DEBUG if (0)
#define lli long long int
#define ldouble long double

struct Problem {
  std::vector<std::string> lines;

  void Solve() {
    for (std::string line; std::getline(std::cin, line);) {
      lines.push_back(line);
    }

    lli ans = 0;
    for (const auto& line : lines) {
      for (int i = 0; i + 8 < line.size(); ++i) {
        if (line[i] != 'm') continue;

        if (line[i + 1] != 'u' || line[i + 2] != 'l' || line[i + 3] != '(' ||
            !std::isdigit(line[i + 4]))
          continue;

        auto GetNum = [&](int j) -> std::tuple<int, int> {
          const int a_start = j;
          while (j + 1 < line.size() && std::isdigit(line[j + 1])) ++j;
          const int a_end = j;
          const int size = a_end - a_start + 1;
          if (size > 3) return std::make_tuple(-1, -1);

          std::istringstream num_in(line.substr(a_start, size));
          int num;
          num_in >> num;
          return std::make_tuple(a_end, num);
        };
        const auto [a_end, a] = GetNum(i + 4);
        i = a_end + 1;

        if (i >= line.size() || line[i] != ',' || !std::isdigit(line[i + 1]))
          continue;

        const auto [b_end, b] = GetNum(i + 1);
        i = b_end + 1;

        if (i >= line.size() || line[i] != ')') continue;

        ans += a * b;
      }
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
