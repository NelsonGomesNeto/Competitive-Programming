#include <bits/stdc++.h>

const int kMaxQueueSize = 1e5;

const std::string kStartMolecule = "e";

using replacement_map = std::map<std::string, std::vector<std::string>>;

struct Machine {
  const replacement_map replacements;
  const replacement_map reverse_replacements;
  const std::vector<std::pair<std::string, std::vector<std::string>>>
      reverse_replacements_list;
  const std::string input;
  Machine(std::istringstream&& sin)
      : replacements([&]() {
          replacement_map rs;
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
        reverse_replacements([&]() {
          replacement_map rs;
          for (const auto& [from, tos] : replacements) {
            for (const auto& to : tos) {
              rs[to].push_back(from);
            }
          }
          return rs;
        }()),
        reverse_replacements_list([&]() {
          std::vector<std::pair<std::string, std::vector<std::string>>> rs;
          for (const auto& [from, tos] : reverse_replacements) {
            rs.emplace_back(from, tos);
          }
          return rs;
        }()),
        input([&]() {
          std::string s;
          sin >> s;
          return s;
        }()) {}
  Machine(const std::string& str) : Machine(std::istringstream(str)) {}

  struct State {
    std::string curr;
    int steps;
    // Most `steps`, smallest `curr` or lexicographically greater `curr`.
    // `input` to `e` takes 6.5s
    // auto operator<=>(const State& other) const {
    //   if (steps == other.steps) return steps <=> other.steps;
    //   if (curr.size() == other.curr.size()) return curr <=> other.curr;
    //   return other.curr.size() <=> curr.size();
    // }
    // `input` to `e` takes 20ms
    // Smallest `curr` or lexicographically greater `curr`.
    // auto operator<=>(const State& other) const {
    //   if (curr.size() == other.curr.size()) return curr <=> other.curr;
    //   return other.curr.size() <=> curr.size();
    // }
    // Smallest `curr` or lexicographically greater `curr`
    // compare `curr` strings if their size is at most 4 apart
    // This unblocks up to 5K input
    auto operator<=>(const State& other) const {
      if (std::abs((int)curr.size() - (int)other.curr.size()) < 4)
        return curr <=> other.curr;
      return other.curr.size() <=> curr.size();
    }
    bool operator==(const State& other) const {
      return steps == other.steps && curr == other.curr;
    }
  };

  int ReverseStepsToMolecule() const {
    std::println("ReverseStepsToMolecule:");
    // std::priority_queue<State> q;
    // Using this to limit the queue size unblocks 5K input.
    std::set<State> q;
    q.emplace(input, 0);
    std::unordered_set<std::string> visited;
    int biggest_step = -1;
    while (!q.empty()) {
      // const auto [curr, steps] = q.top();
      // q.pop();
      const auto [curr, steps] = *q.rbegin();
      q.erase(std::prev(q.end()));
      while (q.size() > kMaxQueueSize) q.erase(q.begin());

      if (const bool inserted = visited.emplace(curr).second; !inserted)
        continue;
      while (visited.size() > kMaxQueueSize) visited.erase(visited.begin());

      if (steps > biggest_step) {
        biggest_step = steps;
        std::println("\tvisited: {} | queue: {} | curr: {} | steps: {}",
                     visited.size(), q.size(), curr.size(), steps);
      }
      if (curr == kStartMolecule) {
        return steps;
      }

      std::string next;
      for (const auto& [from, tos] : reverse_replacements_list) {
        int start = 0;
        while (true) {
          auto pos = curr.find(from, start);
          if (pos == curr.npos) break;
          for (const auto& to : tos) {
            next = curr;
            next.replace(pos, from.size(), to);
            q.emplace(next, steps + 1);
          }
          start = (int)pos + 1;
        }
      }
    }
    assert(false);
  }
};
template <>
struct std::formatter<Machine> {
  constexpr auto parse(std::format_parse_context& ctx) { return ctx.begin(); }
  template <class FormatContext>
  auto format(const Machine& m, FormatContext& ctx) const {
    return std::format_to(
        ctx.out(), "replacements:\n{}\nreverse_replacements:\n{}\ninput:\n\t{}",
        m.replacements |
            std::views::transform(
                [](const std::pair<std::string, std::vector<std::string>>&
                       from_tos) {
                  const auto [from, tos] = from_tos;
                  return std::format("\t{} => {}", from, tos);
                }) |
            std::views::join_with('\n') | std::ranges::to<std::string>(),
        m.reverse_replacements |
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

  const int ans = machine.ReverseStepsToMolecule();
  std::println("ans: {}", ans);

  return 0;
}
