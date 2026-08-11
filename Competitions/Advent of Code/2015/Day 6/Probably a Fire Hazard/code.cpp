#include <bits/stdc++.h>

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
  // Flip this to an array of bitsets
  // Apply the commands row by row
  std::array<std::string, kN> grid;
  friend std::istream& operator>>(std::istream& sin, Decoration& d) {
    while (true) {
      Command command;
      if (!(sin >> command)) break;
      d.commands.push_back(command);
    }
    for (auto& line : d.grid) line.resize(kN, '.');
    return sin;
  }
  void Decorate() {
    for (const auto& c : commands) {
      for (int i = c.loi; i <= c.hii; ++i) {
        for (int j = c.loj; j <= c.hij; ++j) {
          switch (c.op) {
            case kTurnOn:
              grid[i][j] = '#';
              break;
            case kToggle:
              grid[i][j] = grid[i][j] == '#' ? '.' : '#';
              break;
            case kTurnOff:
            default:
              grid[i][j] = '.';
              break;
          }
        }
      }
    }
  }
  void DrawImage() const {
    std::ofstream ofs("image.ppm", std::ios_base::out | std::ios_base::binary);
    ofs << "P6\n" << kN << " " << kN << "\n255\n";
    for (const auto& line : grid) {
      for (const auto c : line) {
        if (c == '#') {
          ofs << (char)255 << (char)255 << (char)255;
        } else {
          ofs << (char)0 << (char)0 << (char)0;
        }
      }
    }
  }

  int OnCount() const {
    int ans = 0;
    for (const auto& line : grid)
      for (const auto c : line) ans += c == '#';
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
        d.grid | std::views::join_with('\n') | std::ranges::to<std::string>());
  }
};

int main() {
  Decoration decoration;
  std::cin >> decoration;

  decoration.Decorate();
  std::println("decoration:\n{}", decoration);
  decoration.DrawImage();

  const int ans = decoration.OnCount();
  std::println("ans: {}", ans);

  return 0;
}
