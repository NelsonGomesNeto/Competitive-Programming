#include <bits/stdc++.h>

template <>
struct std::formatter<Playground> {
  constexpr auto parse(std::format_parse_context& ctx) { return ctx.begin(); }
  template <class FormatContext>
  auto format(const Playground& p, FormatContext& ctx) const {
    // Finally, a oneliner to print a range with custom separators! \o/
    return std::format_to(ctx.out(), "{}",
                          p.jboxes | std::views::transform([](const Pos& pos) {
                            return std::format("\t{}", pos);
                          }) | std::views::join_with('\n') |
                              std::ranges::to<std::string>());
  }
};

int main() { return 0; }
