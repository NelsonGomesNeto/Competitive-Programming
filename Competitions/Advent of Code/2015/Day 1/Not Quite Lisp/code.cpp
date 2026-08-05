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

  int Floor() const {
    int floor = 0;
    for (const auto d : instructions) {
      floor += kDeltaByInstruction[d];
    }
    return floor;
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

    const int ans = map.Floor();
    std::println("ans: {}", ans);
  }

  return 0;
}
