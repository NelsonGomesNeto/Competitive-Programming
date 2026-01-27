#include <bits/stdc++.h>

struct Button {
  std::string effect;
  int effect_mask;
  Button() {}
  Button(std::istream&& sin, const int lights) {
    effect_mask = 0;
    effect.resize(lights, '.');
    for (std::string num; std::getline(sin, num, ',') && !num.empty();) {
      const int pos = std::stoi(num);
      effect[pos] = 'x';
      effect_mask |= 1 << pos;
    }
  }
  Button(const std::string& button_str, const int lights)
      : Button(std::istringstream(button_str), lights) {}
};
template <>
struct std::formatter<Button> {
  constexpr auto parse(std::format_parse_context& ctx) { return ctx.begin(); }
  template <class FormatContext>
  auto format(const Button& b, FormatContext& ctx) const {
    return std::format_to(ctx.out(), "{}({:b})", b.effect, b.effect_mask);
  }
};
struct Machine {
  std::string requirements;
  int requirements_mask;
  std::vector<Button> buttons;
  // Ignore this for now.
  Button joltage;

  Machine(std::istream&& sin) {
    std::string req;
    std::getline(sin, req, ' ');
    requirements = req.substr(1, (int)req.size() - 2);
    for (const auto& [i, c] : requirements | std::views::enumerate) {
      if (c == '#') requirements_mask |= 1 << i;
    }

    for (std::string group; std::getline(sin, group, ' ');) {
      if (group[0] == '(') {
        group = group.substr(1, (int)group.size() - 2);
        buttons.emplace_back(group, (int)requirements.size());
      } else {
        // group = group.substr(1, (int)group.size() - 2);
        // joltage = Button(group, (int)1000);
      }
    }
  }
  Machine(const std::string& machine_str)
      : Machine(std::istringstream(machine_str)) {}

  struct State {
    int mask;
    int presses;
  };
  int Fix() {
    std::queue<State> q;
    q.emplace(0, 0);
    while (!q.empty()) {
      const auto [mask, presses] = q.front();
      q.pop();
      if (mask == requirements_mask) {
        return presses;
      }
      if (presses > 8) {
        break;
      }

      for (const auto& b : buttons) {
        q.emplace(mask ^ b.effect_mask, presses + 1);
      }
    }
    return -1;
  }
};
template <>
struct std::formatter<Machine> {
  constexpr auto parse(std::format_parse_context& ctx) { return ctx.begin(); }
  template <class FormatContext>
  auto format(const Machine& m, FormatContext& ctx) const {
    std::format_to(ctx.out(), "{}({:b})", m.requirements, m.requirements_mask);
    std::format_to(ctx.out(), " | {}",
                   m.buttons | std::views::transform([](const Button& b) {
                     return std::format("{}", b);
                   }) | std::views::join_with(' ') |
                       std::ranges::to<std::string>());
    return std::format_to(ctx.out(), " | {}", m.joltage);
  }
};

struct Factory {
  std::vector<Machine> machines;

  friend std::istream& operator>>(std::istream& sin, Factory& f) {
    f.machines.clear();
    for (std::string line; std::getline(sin, line) && !line.empty();) {
      f.machines.emplace_back(line);
    }
    return sin;
  }

  int Fix() {
    int ans = 0;
    for (auto& m : machines) {
      const int presses = m.Fix();
      assert(presses >= 0);
      std::println("\t{} || {}", presses, m);
      ans += presses;
    }
    return ans;
  }
};
template <>
struct std::formatter<Factory> {
  constexpr auto parse(std::format_parse_context& ctx) { return ctx.begin(); }
  template <class FormatContext>
  auto format(const Factory& f, FormatContext& ctx) const {
    return std::format_to(
        ctx.out(), "{}",
        f.machines | std::views::transform([](const Machine& m) {
          return std::format("\t{}", m);
        }) | std::views::join_with('\n') |
            std::ranges::to<std::string>());
  }
};

int main() {
  Factory factory;
  std::cin >> factory;

  std::println("factory:\n{}", factory);

  const int ans = factory.Fix();
  std::println("Ans: {}", ans);

  return 0;
}
