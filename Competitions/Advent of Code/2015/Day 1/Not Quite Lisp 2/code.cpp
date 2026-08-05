#include <bits/stdc++.h>

const std::array<int, 256> kDeltaByInstruction = []() {
  std::array<int, 256> delta_by_dir;
  delta_by_dir['('] = 1;
  delta_by_dir[')'] = -1;
  return delta_by_dir;
}();

struct Map {
  std::string instructions;
  friend std::istream& operator>>(std::istream& sin, Map& m) {
    sin >> m.instructions;
    return sin;
  }

  int FirstInstructionToBasement() const {
    int floor = 0;
    for (const auto [i, d] : instructions | std::views::enumerate) {
      floor += kDeltaByInstruction[d];
      if (floor < 0) return i + 1;
    }
    return -1;
  }
};
template <>
struct std::formatter<Map> {
  constexpr auto parse(std::format_parse_context& ctx) { return ctx.begin(); }
  template <class FormatContext>
  auto format(const Map& m, FormatContext& ctx) const {
    return std::format_to(ctx.out(), "{}", m.instructions);
  }
};

int main() {
  while (true) {
    Map map;
    if (!(std::cin >> map)) break;
    std::println("Map:\n\t{}", map);

    const int ans = map.FirstInstructionToBasement();
    std::println("ans: {}", ans);
  }

  return 0;
}
