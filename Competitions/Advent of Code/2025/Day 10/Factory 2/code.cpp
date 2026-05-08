#include <bits/stdc++.h>
#define lli long long int

using time_precision = std::chrono::milliseconds;
using joltage_int = short;
const int kInf = 1e4;

std::vector<joltage_int> ReadInts(const std::string& ints_str) {
  std::istringstream sin(ints_str);
  std::vector<joltage_int> ans;
  for (std::string num; std::getline(sin, num, ',') && !num.empty();) {
    ans.push_back((joltage_int)std::stoi(num));
  }
  return ans;
}

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
  void PressAdd(std::vector<joltage_int>& curr) const {
    for (const int p : effect_pos) curr[p] += 1;
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
  }
  Machine(const std::string& machine_str)
      : Machine(std::istringstream(machine_str)) {}

  struct ButtonsCombination {
    std::vector<joltage_int> deltas;
    int presses;
  };
  int CombinePositiveAndParityMasks(const int positive_mask,
                                    const int parity_mask) {
    return (positive_mask << joltage_requirements.size()) | parity_mask;
  }
  std::unordered_map</*(positive_mask << k) | parity_mask*/ int,
                     std::vector<ButtonsCombination>>
      buttons_combinations_by_positive_and_parity_mask;
  std::vector<joltage_int> fill_deltas;
  void FillButtonsCombinations(const int positive_mask,
                               const int parity_mask = 0, const int i = 0,
                               const int presses = 0) {
    if (i == (int)buttons.size()) {
      buttons_combinations_by_positive_and_parity_mask
          .try_emplace(
              CombinePositiveAndParityMasks(positive_mask, parity_mask),
              std::vector<ButtonsCombination>{})
          .first->second.emplace_back(fill_deltas, presses);
      return;
    }
    FillButtonsCombinations(positive_mask, parity_mask, i + 1, presses);
    const Button& b = buttons[i];
    if (std::popcount((uint)(b.effect_mask & positive_mask)) ==
        b.effect_count) {
      b.PressAdd(fill_deltas);
      FillButtonsCombinations(positive_mask, parity_mask ^ b.effect_mask, i + 1,
                              presses + 1);
      b.PressSub(fill_deltas);
    }
  }
  void Precalc() {
    fill_deltas.resize(joltage_requirements.size(), 0);
    for (int positive_mask = 0, end = 1 << joltage_requirements.size();
         positive_mask < end; ++positive_mask) {
      FillButtonsCombinations(positive_mask);
    }
  }

  std::vector<joltage_int> dfs_joltages;
  int Dfs(const int positive_mask, int parity_mask) {
    if (positive_mask == 0) {
      return 0;
    }
    auto it = buttons_combinations_by_positive_and_parity_mask.find(
        CombinePositiveAndParityMasks(positive_mask, parity_mask));
    if (it == buttons_combinations_by_positive_and_parity_mask.end() ||
        it->second.empty()) {
      return kInf;
    }
    const std::vector<ButtonsCombination>& buttons_combinations = it->second;

    int ans = kInf;
    for (const auto& [deltas, presses] : buttons_combinations) {
      const bool valid = [&]() {
        for (const auto [joltage, delta] :
             std::views::zip(dfs_joltages, deltas)) {
          if (delta > joltage) return false;
        }
        return true;
      }();
      if (!valid) continue;

      int new_positive_mask = 0, new_parity_mask = 0;
      for (auto [joltage, delta] :
           std::views::zip(dfs_joltages, deltas) | std::views::reverse) {
        joltage -= delta;
        joltage >>= 1;
        new_positive_mask = (new_positive_mask << 1) | (joltage > 0);
        new_parity_mask = (new_parity_mask << 1) | (joltage & 1);
      }
      ans =
          std::min(ans, presses + 2 * Dfs(new_positive_mask, new_parity_mask));
      for (auto [joltage, delta] : std::views::zip(dfs_joltages, deltas)) {
        joltage <<= 1;
        joltage += delta;
      }
    }
    return ans;
  }

  int DfsFix() {
    const auto [positive_mask, parity_mask] = [&]() {
      int positive_mask = 0, parity_mask = 0;
      for (const auto [i, v] : joltage_requirements | std::views::enumerate) {
        positive_mask |= (v > 0) << i;
        parity_mask |= (v & 1) << i;
      }
      return std::make_pair(positive_mask, parity_mask);
    }();
    dfs_joltages = joltage_requirements;
    const int ans = Dfs(positive_mask, parity_mask);
    return ans;
  }

  int Fix() { return DfsFix(); }
};
template <>
struct std::formatter<Machine> {
  constexpr auto parse(std::format_parse_context& ctx) { return ctx.begin(); }
  template <class FormatContext>
  auto format(const Machine& m, FormatContext& ctx) const {
    std::format_to(ctx.out(), "{}",
                   m.buttons | std::views::transform([](const Button& b) {
                     return std::format("{}", b);
                   }) | std::views::join_with(' ') |
                       std::ranges::to<std::string>());
    std::format_to(ctx.out(), " | {}", m.joltage_requirements);
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

  void Precalc() {
    for (auto& m : machines) {
      m.Precalc();
    }
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
  {
    const auto start = std::chrono::high_resolution_clock::now();
    std::cin >> factory;
    std::println("factory:\n{}", factory);
    const auto end = std::chrono::high_resolution_clock::now();
    const auto duration =
        std::chrono::duration_cast<time_precision>(end - start);
    std::println("time Read: {}", duration);
  }

  {
    const auto start = std::chrono::high_resolution_clock::now();
    factory.Precalc();
    const auto end = std::chrono::high_resolution_clock::now();
    const auto duration =
        std::chrono::duration_cast<time_precision>(end - start);
    std::println("time Precalc: {}", duration);
  }

  {
    const auto start = std::chrono::high_resolution_clock::now();
    const int ans = factory.Fix();
    std::println("Ans: {}", ans);
    const auto end = std::chrono::high_resolution_clock::now();
    const auto duration =
        std::chrono::duration_cast<time_precision>(end - start);
    std::println("time Fix: {}", duration);
  }

  return 0;
}
