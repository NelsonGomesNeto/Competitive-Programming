#include <bits/stdc++.h>

struct Reindeer {
  const std::string name;
  const int speed, stamina, rest;
  Reindeer(const std::vector<std::string>& words)
      : name(words[0]),
        speed(std::stoi(words[3])),
        stamina(std::stoi(words[6])),
        rest(std::stoi(words[13])) {}
  Reindeer(std::istringstream&& sin)
      : Reindeer([&]() {
          std::vector<std::string> words;
          for (std::string word; sin >> word;) words.push_back(word);
          return words;
        }()) {}
  Reindeer(const std::string& str) : Reindeer(std::istringstream(str)) {}

  int Run(const int seconds) const {
    int t = 0, d = 0;
    // Is it possible to do this in O(1)?
    while (t <= seconds) {
      const int rem = seconds - t;
      const int allowed = std::min(rem, stamina);
      d += speed * allowed;
      t += stamina + rest;
    }
    return d;
  }
};
template <>
struct std::formatter<Reindeer> {
  constexpr auto parse(std::format_parse_context& ctx) { return ctx.begin(); }
  template <class FormatContext>
  auto format(const Reindeer& r, FormatContext& ctx) const {
    return std::format_to(ctx.out(), "{} {}km/s for {}s and rest for {}s",
                          r.name, r.speed, r.stamina, r.rest);
  }
};

struct Olympics {
  const std::vector<Reindeer> reindeers;
  Olympics(std::istringstream&& sin)
      : reindeers([&]() {
          std::vector<Reindeer> rs;
          for (std::string line; std::getline(sin, line);) {
            rs.emplace_back(line);
          }
          return rs;
        }()) {}
  Olympics(const std::string& str) : Olympics(std::istringstream(str)) {}

  int Run(const int seconds) const {
    std::println("run:");
    std::vector<std::pair<int, int>> distances(reindeers.size());
    for (const auto& [i, r] : reindeers | std::views::enumerate) {
      distances[i] = {r.Run(seconds), i};
    }
    std::ranges::sort(distances, std::greater());
    std::println("{}", distances | std::views::transform([&](const auto& di) {
                         const auto [d, i] = di;
                         return std::format("\t{} {}km", reindeers[i].name, d);
                       }) | std::views::join_with('\n') |
                           std::ranges::to<std::string>());
    return distances[0].first;
  }
};
template <>
struct std::formatter<Olympics> {
  constexpr auto parse(std::format_parse_context& ctx) { return ctx.begin(); }
  template <class FormatContext>
  auto format(const Olympics& o, FormatContext& ctx) const {
    return std::format_to(
        ctx.out(), "{}",
        o.reindeers | std::views::transform([](const Reindeer& r) {
          return std::format("\t{}", r);
        }) | std::views::join_with('\n') |
            std::ranges::to<std::string>());
  }
};

// Let's try to read the input differently this time.
// Maybe the boiler plate becomes much smaller.
// It looks cleaner and we get const \o/
int main() {
  std::stringstream ss;
  ss << std::cin.rdbuf();
  std::string input = ss.str();

  Olympics olympics(input);
  std::println("olympics:\n{}", olympics);

  const int ans = olympics.Run(/*seconds=*/2503);
  std::println("ans: {}", ans);

  return 0;
}
