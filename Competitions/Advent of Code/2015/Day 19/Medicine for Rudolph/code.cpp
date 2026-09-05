#include <bits/stdc++.h>

struct Machine {
  const std::map<std::string, std::vector<std::string>> replacements;
  const std::string input;
  Machine(std::istringstream&& sin)
      : replacements([&]() {
          std::map<std::string, std::vector<std::string>> rs;
          std::string from, to;
          for (std::string line; std::getline(sin, line) && !line.empty();) {
            std::istringstream lin(line);
            lin >> from;
            lin.ignore(std::numeric_limits<std::streamsize>::max(), ' ');
            lin.ignore(std::numeric_limits<std::streamsize>::max(), ' ');
            lin >> to;
            rs[from].push_back(to);
          }
          return rs;
        }()),
        input([&]() {
          std::string s;
          sin >> s;
          return s;
        }()) {}
  Machine(const std::string& str) : Machine(std::istringstream(str)) {}

  int DistinctMolecules() const {
    std::println("DistinctMolecules:");
    std::set<std::string> molecules;
    for (const auto& [from, tos] : replacements) {
      for (const auto& to : tos) {
        int start = 0;
        while (true) {
          std::string curr = input;
          auto pos = curr.find(from, start);
          if (pos == curr.npos) break;
          curr.replace(pos, from.size(), to);
          molecules.insert(curr);
          start = (int)pos + 1;
        }
      }
    }
    std::println("\t{}", molecules |
                             std::views::join_with(std::string_view("\n\t")) |
                             std::ranges::to<std::string>());
    return (int)molecules.size();
  }
};
template <>
struct std::formatter<Machine> {
  constexpr auto parse(std::format_parse_context& ctx) { return ctx.begin(); }
  template <class FormatContext>
  auto format(const Machine& m, FormatContext& ctx) const {
    return std::format_to(
        ctx.out(), "replacements:\n{}\ninput:\n\t{}",
        m.replacements |
            std::views::transform(
                [](const std::pair<std::string, std::vector<std::string>>&
                       from_tos) {
                  const auto [from, tos] = from_tos;
                  return std::format("\t{} => {}", from, tos);
                }) |
            std::views::join_with('\n') | std::ranges::to<std::string>(),
        m.input);
  }
};

int main() {
  const std::string input(std::istreambuf_iterator<char>(std::cin), {});

  const Machine machine(input);
  std::println("machine:\n{}", machine);

  const int ans = machine.DistinctMolecules();
  std::println("ans: {}", ans);

  return 0;
}
