#include <bits/stdc++.h>
#define lli long long int

using time_precision = std::chrono::seconds;
using joltage_int = short;
const int kInf = 1e6;

std::vector<joltage_int> ReadInts(const std::string& ints_str) {
  std::istringstream sin(ints_str);
  std::vector<joltage_int> ans;
  for (std::string num; std::getline(sin, num, ',') && !num.empty();) {
    ans.push_back((joltage_int)std::stoi(num));
  }
  return ans;
}

struct VectorHash {
  size_t operator()(const std::vector<joltage_int>& v) const {
    std::hash<joltage_int> hasher;
    size_t seed = 0;
    for (joltage_int i : v) {
      seed ^= hasher(i) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
    }
    return seed;
  }
};

struct Button {
  std::string effect;
  int effect_mask;
  std::vector<int> effect_pos;
  int effect_count;
  Button() {}
  Button(std::istream&& sin, const int lights) {
    effect_mask = 0;
    effect.resize(lights, '.');
    effect_pos.clear();
    for (std::string num; std::getline(sin, num, ',') && !num.empty();) {
      const int pos = std::stoi(num);
      effect[pos] = 'x';
      effect_pos.push_back(pos);
      effect_mask |= 1 << pos;
    }
    effect_count = effect_pos.size();
  }
  Button(const std::string& button_str, const int lights)
      : Button(std::istringstream(button_str), lights) {}

  std::vector<joltage_int> Press(std::vector<joltage_int> curr) const {
    for (const int p : effect_pos) curr[p] -= 1;
    return curr;
  }
  void PressAdd(std::vector<joltage_int>& curr, const int delta) const {
    for (const int p : effect_pos) curr[p] += delta;
  }
  void PressSub(std::vector<joltage_int>& curr) const {
    for (const int p : effect_pos) curr[p] -= 1;
  }
};
template <>
struct std::formatter<Button> {
  constexpr auto parse(std::format_parse_context& ctx) { return ctx.begin(); }
  template <class FormatContext>
  auto format(const Button& b, FormatContext& ctx) const {
    return std::format_to(ctx.out(), "{}", b.effect);
  }
};
struct Machine {
  std::string light_requirements;  // Ignore this one for this part
  std::vector<Button> buttons;
  std::vector<joltage_int> joltage_requirements;

  Machine() {}
  Machine(std::istream&& sin) {
    std::string req;
    std::getline(sin, req, ' ');
    light_requirements = req.substr(1, (int)req.size() - 2);

    for (std::string group; std::getline(sin, group, ' ');) {
      if (group[0] == '(') {
        group = group.substr(1, (int)group.size() - 2);
        buttons.emplace_back(group, (int)light_requirements.size());
      } else {
        group = group.substr(1, (int)group.size() - 2);
        joltage_requirements = ReadInts(group);
      }
    }

    Precalc();
  }
  Machine(const std::string& machine_str)
      : Machine(std::istringstream(machine_str)) {}

  std::vector<std::vector<bool>> reachable_mod2masks_by_available_buttons;
  void FillReachableMod2(const int positive_mask, const int parity_mask = 0,
                         const int i = 0) {
    if (i == (int)buttons.size()) {
      reachable_mod2masks_by_available_buttons[positive_mask][parity_mask] =
          true;
      return;
    }
    FillReachableMod2(positive_mask, parity_mask, i + 1);
    const Button& b = buttons[i];
    if (std::popcount((uint)(b.effect_mask & positive_mask)) == b.effect_count)
      FillReachableMod2(positive_mask, parity_mask ^ b.effect_mask, i + 1);
  }
  std::vector<std::vector<std::reference_wrapper<const Button>>>
      buttons_by_joltage;
  struct MetaButton {
    std::reference_wrapper<const Button> button;
    std::vector<int> joltage_positions_to_zero;
  };
  std::vector<MetaButton> meta_buttons;
  void BuildMetaButtons() {
    buttons_by_joltage.resize(joltage_requirements.size(), {});
    for (const auto& b : buttons) {
      for (const auto pos : b.effect_pos) {
        buttons_by_joltage[pos].emplace_back(b);
      }
    }
    for (int joltage_i = 0; joltage_i < (int)joltage_requirements.size();
         ++joltage_i) {
      std::ranges::sort(buttons_by_joltage[joltage_i],
                        [](const Button& a, const Button& b) {
                          return a.effect_count > b.effect_count;
                        });
    }

    std::vector<std::tuple<int, int, int>> buttons_by_joltage_order;
    buttons_by_joltage_order.reserve(buttons_by_joltage.size());
    for (const auto [i, bs] : buttons_by_joltage | std::views::enumerate) {
      buttons_by_joltage_order.emplace_back(
          (int)bs.size(), -(int)joltage_requirements[i], (int)i);
    }
    std::ranges::sort(buttons_by_joltage_order);

    std::set<int> done_buttons;
    meta_buttons.reserve(buttons.size());
    for (const auto [bs_size, joltage_requirement, joltage_i] :
         buttons_by_joltage_order) {
      for (const Button& b : buttons_by_joltage[joltage_i]) {
        if (const bool inserted = done_buttons.insert(b.effect_mask).second;
            !inserted)
          continue;
        meta_buttons.emplace_back(b);
      }
    }

    // TODO: Maybe there is another way to sort the `meta_buttons` in a way
    // that maximizes the amount of `joltage_positions_to_zero` in the start.
    // That is where the biggest prune comes from anyways.
    for (int joltage_i = 0; joltage_i < (int)joltage_requirements.size();
         ++joltage_i) {
      auto reversed_meta_buttons_view = meta_buttons | std::views::reverse;
      auto it = std::ranges::find_if(
          reversed_meta_buttons_view, [&](const MetaButton& meta_button) {
            const Button& mb = meta_button.button;
            for (const Button& b : buttons_by_joltage[joltage_i]) {
              if (mb.effect_mask == b.effect_mask) return true;
            }
            return false;
          });
      assert(it != reversed_meta_buttons_view.end());
      it->joltage_positions_to_zero.push_back(joltage_i);
    }
  }
  void Precalc() {
    reachable_mod2masks_by_available_buttons.resize(
        1 << joltage_requirements.size(),
        std::vector<bool>(1 << joltage_requirements.size(), false));
    for (int positive_mask = 0, end = 1 << joltage_requirements.size();
         positive_mask < end; ++positive_mask) {
      FillReachableMod2(positive_mask);
    }
    BuildMetaButtons();
  }

  std::vector<joltage_int> dfs_joltages;
  int dfs_best_ans;
  void Dfs(const int positive_mask, int parity_mask, const int i = 0,
           const int presses = 0) {
    if (positive_mask == 0) {
      dfs_best_ans = presses;
      return;
    }
    if (i == meta_buttons.size()) {
      return;
    }
    if (!reachable_mod2masks_by_available_buttons[positive_mask][parity_mask]) {
      return;
    }
    if (presses + *std::ranges::max_element(dfs_joltages) >= dfs_best_ans) {
      return;
    }

    const std::vector<int>& joltage_positions_to_zero =
        meta_buttons[i].joltage_positions_to_zero;
    const Button& b = meta_buttons[i].button;
    auto Next = [&](int next_positive_mask, const int next_parity_mask,
                    const int next_i, const int next_presses) {
      for (const int joltage_i : joltage_positions_to_zero) {
        if (dfs_joltages[joltage_i] > 0) return;
      }
      for (const auto [j, joltage] : dfs_joltages | std::views::enumerate) {
        if (joltage > 0) continue;
        next_positive_mask &= ~(1 << j);
      }
      Dfs(next_positive_mask, next_parity_mask, next_i, next_presses);
    };

    Next(positive_mask, parity_mask, i + 1, presses);
    const joltage_int available_presses = [&]() {
      joltage_int available_presses = std::numeric_limits<joltage_int>::max();
      for (const int pos : b.effect_pos) {
        available_presses = std::min(available_presses, dfs_joltages[pos]);
      }
      return available_presses;
    }();
    for (int p = 1; p <= available_presses; ++p) {
      b.PressSub(dfs_joltages);
      parity_mask ^= b.effect_mask;
      Next(positive_mask, parity_mask, i + 1, p + presses);
    }
    b.PressAdd(dfs_joltages, available_presses);
  }

  int DfsFix() {
    assert(meta_buttons.size() == buttons.size());
    const auto [positive_mask, parity_mask] = [&]() {
      int positive_mask = 0, parity_mask = 0;
      for (const auto [i, v] : joltage_requirements | std::views::enumerate) {
        positive_mask |= ((v > 0) ? 1 : 0) << i;
        parity_mask |= ((v & 1) ? 1 : 0) << i;
      }
      return std::make_pair(positive_mask, parity_mask);
    }();
    dfs_joltages = joltage_requirements;
    dfs_best_ans = std::numeric_limits<int>::max();
    Dfs(positive_mask, parity_mask);
    return dfs_best_ans;
  }

  int Fix() { return DfsFix(); }
};
template <>
struct std::formatter<Machine> {
  constexpr auto parse(std::format_parse_context& ctx) { return ctx.begin(); }
  template <class FormatContext>
  auto format(const Machine& m, FormatContext& ctx) const {
    int mini = std::numeric_limits<int>::max();
    for (const auto& bs : m.buttons_by_joltage) {
      mini = std::min(mini, (int)bs.size());
    }
    // std::format_to(ctx.out(), "{} | [{}]", mini,
    //                m.buttons_by_joltage | std::views::enumerate |
    //                    std::views::transform([&](const auto& ibs) {
    //                      const auto [i, bs] = ibs;
    //                      return std::format(
    //                          "({}, {})", m.joltage_requirements[i],
    //                          bs.size());
    //                    }) |
    //                    std::views::join_with(std::string_view(", ")) |
    //                    std::ranges::to<std::string>());
    std::format_to(ctx.out(), "{}",
                   m.buttons | std::views::transform([](const Button& b) {
                     return std::format("{}", b);
                   }) | std::views::join_with(' ') |
                       std::ranges::to<std::string>());
    std::format_to(ctx.out(), " | {}", m.joltage_requirements);
    std::format_to(
        ctx.out(), " | {} [{}]", mini,
        m.buttons_by_joltage |
            std::views::transform(
                [](const std::vector<std::reference_wrapper<const Button>>&
                       bs) { return std::format("{}", bs.size()); }) |
            std::views::join_with(std::string_view(", ")) |
            std::ranges::to<std::string>());
    return ctx.out();
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
      std::println("\t{} || {}", presses, m);
      std::fflush(stdout);
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
