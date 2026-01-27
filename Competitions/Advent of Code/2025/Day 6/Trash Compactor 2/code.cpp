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
    return std::format_to(ctx.out(), "{} {} = {}", p.numbers, p.op, p.result);
  }
};

struct Homework {
  std::vector<Problem> problems;

  friend std::istream& operator>>(std::istream& sin, Homework& h) {
    std::vector<std::string> lines;
    for (std::string line; std::getline(sin, line) && !line.empty();) {
      lines.push_back(line);
      DEBUG std::println("line: {}", lines.back());
    }
    std::vector<int> ends;
    // Use the operations line to parse the dimensions of each problem.
    for (int i = 0; i < (int)lines.back().size(); ++i) {
      int j = i;
      // read operation
      ++j;
      // ignore spaces until the next operation (or end)
      while (j < (int)lines.back().size() && lines.back()[j] == ' ') ++j;
      if (j == (int)lines.back().size()) {
        // reached the end
        ends.push_back(j - 1);
      } else {
        // reached the next operation (-1 for it and -1 for the spacing)
        ends.push_back(j - 2);
      }
      i = j + 1;
    }

    std::vector<std::vector<std::string>> splitted_lines;
    splitted_lines.reserve(lines.size());
    for (const auto& line : lines) {
      int i = 0;
      splitted_lines.emplace_back();
      for (const int end : ends) {
        splitted_lines.back().push_back(line.substr(i, end - i + 1));
        i = end + 2;
      }
      std::println("splitted_lines: {}", splitted_lines.back());
    }

    std::vector<std::vector<std::string>> columns(splitted_lines[0].size());
    for (int j = 0; j < (int)splitted_lines[0].size(); ++j) {
      const int problem_columns = (int)splitted_lines[0][j].size();
      columns[j].resize(problem_columns, "");
      for (int d = 0; d < problem_columns; ++d) {
        for (int i = 0; i < (int)splitted_lines.size() - 1; ++i) {
          const int pos = problem_columns - d - 1;
          const char digit = splitted_lines[i][j][pos];
          columns[j][d].push_back(digit);
        }
      }
      columns[j].push_back(splitted_lines.back()[j]);
    }
    std::ranges::reverse(columns);
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
