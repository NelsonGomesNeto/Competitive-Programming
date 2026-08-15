#include <bits/stdc++.h>
#define lli long long int

const int kN = 1000;

enum Op { kTurnOn = 0, kToggle = 1, kTurnOff = 2 };
const std::array<std::string, 3> kOpName = {"turn_on", "toggle", "turn_off"};
struct Command {
  Op op;
  int loi, loj, hii, hij;
  friend std::istream& operator>>(std::istream& sin, Command& c) {
    std::string line;
    if (!std::getline(sin, line)) return sin;
    if (line.starts_with("toggle"))
      c.op = Op::kToggle;
    else if (line.starts_with("turn on"))
      c.op = Op::kTurnOn;
    else
      c.op = Op::kTurnOff;
    std::istringstream linein(line.substr(kOpName[c.op].size()));
    linein >> c.loj;
    linein.ignore(1);  // ignore `,`
    linein >> c.loi;
    linein.ignore(9);  // ignore ` through `
    linein >> c.hij;
    linein.ignore(1);  // ignore `,`
    linein >> c.hii;
    return sin;
  }
};
template <>
struct std::formatter<Command> {
  constexpr auto parse(std::format_parse_context& ctx) { return ctx.begin(); }
  template <class FormatContext>
  auto format(const Command& c, FormatContext& ctx) const {
    return std::format_to(ctx.out(), "{:8} | {} {} | {} {}", kOpName[c.op],
                          c.loi, c.loj, c.hii, c.hij);
  }
};
struct Decoration {
  std::vector<Command> commands;
  // Apply the commands row by row
  std::array<std::array<int, kN>, kN> grid;
  friend std::istream& operator>>(std::istream& sin, Decoration& d) {
    while (true) {
      Command command;
      if (!(sin >> command)) break;
      d.commands.push_back(command);
    }
    for (auto& line : d.grid) std::ranges::fill(line, 0);
    return sin;
  }
  void Decorate() {
    for (const auto& c : commands) {
      for (int i = c.loi; i <= c.hii; ++i) {
        for (int j = c.loj; j <= c.hij; ++j) {
          switch (c.op) {
            case kTurnOn:
              grid[i][j] += 1;
              break;
            case kToggle:
              grid[i][j] += 2;
              break;
            case kTurnOff:
            default:
              grid[i][j] = std::max(grid[i][j] - 1, 0);
              break;
          }
        }
      }
    }
  }
  void DrawImage() const {
    const std::vector<std::vector<int>> kRainbow = {
        {255, 0, 0},     // 0 red
        {255, 127, 0},   // 1 orange
        {255, 255, 0},   // 2 yellow
        {0, 128, 0},     // 3 green
        {0, 0, 255},     // 4 blue
        {75, 0, 130},    // 5 indigo
        {138, 43, 226},  // 6 violeta
    };
    const int max_brightness = [&]() {
      int max_brightness = 0;
      for (const auto& line : grid) {
        for (const auto c : line) {
          max_brightness = std::max(max_brightness, c);
        }
      }
      return max_brightness;
    }();
    std::ofstream ofs("image.ppm", std::ios_base::out | std::ios_base::binary);
    ofs << "P6\n" << kN << " " << kN << "\n255\n";
    for (const auto& line : grid) {
      for (const auto c : line) {
        const double frac = (double)c / max_brightness;
        const int color = 255 * (kRainbow.size() - 2) * frac;
        const int ri = color / 255;
        const int t = color % 255;
        for (const auto [prv, nxt] :
             std::views::zip(kRainbow[ri], kRainbow[ri + 1])) {
          const int delta = nxt - prv;
          const double p = (double)t / 255;
          ofs << (uint8_t)(prv + p * delta);
        }
      }
    }
  }

  lli TotalBrightness() const {
    lli ans = 0;
    for (const auto& line : grid)
      for (const auto c : line) ans += c;
    return ans;
  }
};
template <>
struct std::formatter<Decoration> {
  constexpr auto parse(std::format_parse_context& ctx) { return ctx.begin(); }
  template <class FormatContext>
  auto format(const Decoration& d, FormatContext& ctx) const {
    return std::format_to(
        ctx.out(), "\tcommands:\n{}\n\tgrid:\n{}",
        d.commands | std::views::transform([](const Command& c) {
          return std::format("{}", c);
        }) | std::views::join_with('\n') |
            std::ranges::to<std::string>(),
        d.grid | std::views::transform([](const auto& line) {
          return std::format("{}",
                             line | std::views::transform([](const int p) {
                               return std::format("{}", p % 10);
                             }) | std::views::join |
                                 std::ranges::to<std::string>());
        }) | std::views::join_with('\n') |
            std::ranges::to<std::string>());
  }
};

int main() {
  Decoration decoration;
  std::cin >> decoration;

  decoration.Decorate();
  std::println("decoration:\n{}", decoration);
  decoration.DrawImage();

  const lli ans = decoration.TotalBrightness();
  std::println("ans: {}", ans);

  return 0;
}
