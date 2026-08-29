#include <bits/stdc++.h>
#define ANIMATE if (0)

const int kAnimationSeconds = 10;
const int kSeconds = 2503;
const int kDtNanoseconds = (double)kAnimationSeconds / kSeconds * 1000000000;
const std::string_view kClearScreen = "\033[1J";
const std::string_view kMoveTo00 = "\033[1;1H";
const std::string_view kResetColor = "\033[0m";
const std::vector<std::string> kColors = {
    "\033[38;2;255;0;0m",      // red
    "\033[38;2;0;255;0m",      // green
    "\033[38;2;255;255;0m",    // yellow
    "\033[38;2;0;0;255m",      // blue
    "\033[38;2;255;0;255m",    // magenta
    "\033[38;2;0;255;255m",    // cyan
    "\033[38;2;255;255;255m",  // white
    "\033[38;2;252;127;0m",    // orange
    "\033[38;2;255;105;180m",  // pink
};

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
    // Is it possible to do this in O(1)? YES!
    // int t = 0, d = 0;
    // while (t <= seconds) {
    //   const int rem = seconds - t;
    //   const int allowed = std::min(rem, stamina);
    //   d += speed * allowed;
    //   t += stamina + rest;
    // }
    const int block_size = stamina + rest;
    const int blocks = seconds / block_size;
    const int rem = seconds % block_size;
    const int d = (blocks * stamina + std::min(rem, stamina)) * speed;
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
  const int n;
  Olympics(std::istringstream&& sin)
      : reindeers([&]() {
          std::vector<Reindeer> rs;
          for (std::string line; std::getline(sin, line);) {
            rs.emplace_back(line);
          }
          return rs;
        }()),
        n(reindeers.size()) {}
  Olympics(const std::string& str) : Olympics(std::istringstream(str)) {}

  int Run(const int seconds) const {
    std::println("run:");
    std::vector<std::pair<int, int>> points(n);
    for (int i = 0; i < n; ++i) points[i] = {0, i};
    std::vector<std::pair<int, int>> distances(n);
    for (int t = 1; t <= seconds; ++t) {
      for (const auto& [i, r] : reindeers | std::views::enumerate) {
        distances[i] = {r.Run(t), i};
      }
      std::ranges::sort(distances, std::greater());
      for (int i = 0; i < n && distances[i].first == distances[0].first; ++i) {
        points[distances[i].second].first += 1;
      }
    }
    std::ranges::sort(points, std::greater());
    std::println("{}", points | std::views::transform([&](const auto& pi) {
                         const auto [p, i] = pi;
                         return std::format("\t{:7} | {:4}points | {:4}km",
                                            reindeers[i].name, p,
                                            reindeers[i].Run(seconds));
                       }) | std::views::join_with('\n') |
                           std::ranges::to<std::string>());
    return points[0].first;
  }

  void Animation(const int seconds) const {
    const int max_distance =
        std::ranges::max(reindeers | std::views::transform([&](const auto& r) {
                           return r.Run(seconds);
                         }));
    const int max_name =
        std::ranges::max(reindeers | std::views::transform([&](const auto& r) {
                           return r.name.size();
                         }));
    const int run_space = 90 - max_name - 2 - 1;
    std::string scene;
    scene.reserve(n * 200);
    for (int t = 0; t <= seconds; ++t) {
      scene.clear();
      for (const auto& [i, r] : reindeers | std::views::enumerate) {
        const int d = r.Run(t);
        const bool resting = r.Run(t + 1) == d;
        std::string trace =
            std::string(std::round((double)d / max_distance * run_space), '#');
        std::format_to(std::back_inserter(scene), "{}{:{}}{} |{}{}{}{}{}|\n",
                       kColors[i], r.name, max_name, kResetColor, kColors[i],
                       trace, resting ? '@' : '>',
                       std::string(run_space - (int)trace.size(), ' '),
                       kResetColor);
      }
      std::print("{}{}{}", kClearScreen, kMoveTo00, scene);
      std::this_thread::sleep_for(std::chrono::nanoseconds(kDtNanoseconds));
    }
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
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  std::stringstream ss;
  ss << std::cin.rdbuf();
  std::string input = ss.str();
  Olympics olympics(input);

  ANIMATE olympics.Animation(kSeconds);

  std::println("olympics:\n{}", olympics);

  const int ans = olympics.Run(kSeconds);
  std::println("ans: {}", ans);

  return 0;
}
