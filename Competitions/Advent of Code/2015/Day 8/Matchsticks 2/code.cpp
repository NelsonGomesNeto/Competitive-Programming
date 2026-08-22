#include <bits/stdc++.h>

std::string Unescape(const std::string& s) {
  std::string t;
  t.reserve(s.size());
  bool escaping = false;
  int hex_value = -1;
  for (const auto c : s) {
    if (escaping) {
      if (c == '\\') {
        t.push_back('\\'), escaping = false;
      } else if (c == '\"') {
        t.push_back('\"'), escaping = false;
      } else if (c == 'x') {
        hex_value = -1;
      } else if (hex_value == -1) {
        hex_value = c - '0';
      } else {
        hex_value = hex_value * 16 + (c - '0');
        t.push_back((char)hex_value);
        escaping = false;
      }
    } else if (c == '\\') {
      escaping = true;
    } else {
      t.push_back(c);
    }
  }
  return t;
}

std::string Escape(const std::string& s) {
  std::string t;
  t.reserve(s.size());
  t.push_back('\"');
  for (const auto c : s) {
    if (c == '\"' || c == '\\') t.push_back('\\');
    t.push_back(c);
  }
  t.push_back('\"');
  return t;
}

struct List {
  std::vector<std::string> names;
  friend std::istream& operator>>(std::istream& sin, List& l) {
    for (std::string line; std::getline(sin, line);) {
      l.names.push_back(line);
    }
    return sin;
  }

  int TotalDiff() const {
    int ans = 0;
    for (const auto& name : names) {
      const int original_size = (int)name.size();
      const std::string escaped_name = Escape(name);
      const int escaped_size = escaped_name.size();
      ans += escaped_size - original_size;
      std::println("\t{}({}) -> {}({})", name, original_size, escaped_name,
                   escaped_size);
    }
    return ans;
  }
};
template <>
struct std::formatter<List> {
  constexpr auto parse(std::format_parse_context& ctx) { return ctx.begin(); }
  template <class FormatContext>
  auto format(const List& l, FormatContext& ctx) const {
    return std::format_to(ctx.out(), "{}",
                          l.names | std::views::transform([](const auto& name) {
                            return std::format("\t|{}|", name);
                          }) | std::views::join_with('\n') |
                              std::ranges::to<std::string>());
  }
};

int main() {
  List list;
  std::cin >> list;

  std::println("list:\n{}", list);

  std::println("TotalDiff (escape):");
  const int ans = list.TotalDiff();
  std::println("ans: {}", ans);

  return 0;
}
