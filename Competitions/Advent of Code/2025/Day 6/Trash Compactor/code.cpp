#include <bits/stdc++.h>
#ifdef DEB
#define DEBUG if (1)
#else
#define DEBUG if (0)
#endif
#define lli long long int

struct Problem {
  std::vector<lli> numbers;
  char op;
  lli result;

  Problem(const std::vector<std::string>& raw_problem) {
    for (const auto& number_str :
         raw_problem | std::views::take((int)raw_problem.size() - 1)) {
      numbers.emplace_back(std::stoll(number_str));
    }
    op = raw_problem.back()[0];

    result = op == '+'
                 ? std::reduce(numbers.begin(), numbers.end(), 0LL, std::plus())
                 : std::reduce(numbers.begin(), numbers.end(), 1LL,
                               std::multiplies());
  }
};
template <>
struct std::formatter<Problem> {
  constexpr auto parse(std::format_parse_context& ctx) { return ctx.begin(); }
  template <class FormatContext>
  auto format(const Problem& p, FormatContext& ctx) const {
    return std::format_to(ctx.out(), "{} {} = {}", p.numbers, p.op,
                          p.result);
  }
};

struct Homework {
  std::vector<Problem> problems;

  friend std::istream& operator>>(std::istream& sin, Homework& h) {
    std::vector<std::vector<std::string>> lines;
    for (std::string line; std::getline(sin, line) && !line.empty();) {
      std::istringstream sline(line);
      lines.emplace_back();
      for (std::string item; sline >> item;) {
        lines.back().push_back(item);
      }
      DEBUG std::println("line: {}", lines.back());
    }

    std::vector<std::vector<std::string>> columns(
        lines[0].size(), std::vector<std::string>(lines.size()));
    for (int i = 0; i < (int)lines.size(); ++i) {
      assert(lines[i].size() == lines[0].size());
      for (int j = 0; j < (int)lines[0].size(); ++j) {
        columns[j][i] = lines[i][j];
      }
    }
    DEBUG {
      for (int i = 0; i < (int)columns.size(); ++i) {
        std::println("column: {}", columns[i]);
      }
    }

    for (const auto& raw_problem : columns) {
      h.problems.emplace_back(raw_problem);
    }

    return sin;
  }

  lli Solve() const {
    lli ans = 0;
    for (const auto& p : problems) {
      ans += p.result;
    }
    return ans;
  }
};
template <>
struct std::formatter<Homework> {
  constexpr auto parse(std::format_parse_context& ctx) { return ctx.begin(); }
  template <class FormatContext>
  auto format(const Homework& h, FormatContext& ctx) const {
    for (const auto& p :
         h.problems | std::views::take((int)h.problems.size() - 1)) {
      std::format_to(ctx.out(), "{}\n", p);
    }
    return std::format_to(ctx.out(), "{}", h.problems.back());
  }
};

int main() {
  Homework homework;
  std::cin >> homework;

  std::println("homework:\n{}", homework);

  const lli ans = homework.Solve();
  std::println("Ans: {}", ans);

  return 0;
}
