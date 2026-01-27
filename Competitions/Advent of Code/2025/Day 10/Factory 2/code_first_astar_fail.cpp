#include <bits/stdc++.h>

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
  }
  Button(const std::string& button_str, const int lights)
      : Button(std::istringstream(button_str), lights) {}

  std::vector<joltage_int> Press(std::vector<joltage_int> curr) const {
    for (const int p : effect_pos) curr[p] -= 1;
    return curr;
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
  int joltage_requirements_mask;
  int mask_count;

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
    mask_count = 1 << (int)joltage_requirements.size();
    joltage_requirements_mask = 0;
    for (const auto& [i, v] : joltage_requirements | std::views::enumerate) {
      if (v & 1) joltage_requirements_mask |= 1 << i;
    }
  }
  Machine(const std::string& machine_str)
      : Machine(std::istringstream(machine_str)) {}

  std::vector<bool> all_reachable_mask_parities;
  void FindAllPossibleParities(const int i = 0, const int curr = 0) {
    if (i == (int)buttons.size()) {
      all_reachable_mask_parities[curr] = true;
      return;
    }
    FindAllPossibleParities(i + 1, curr);
    FindAllPossibleParities(i + 1, curr ^ buttons[i].effect_mask);
  }
  void Precalc() {
    all_reachable_mask_parities.resize(mask_count, false);
    FindAllPossibleParities();
    std::println("\t\tall_reachable_mask_parities: {} | {}",
                 std::ranges::count(all_reachable_mask_parities, true),
                 all_reachable_mask_parities.size());
    std::fflush(stdout);
  }

  int DistFrom(const std::vector<joltage_int>& mask) {
    int dist = std::reduce(mask.begin(), mask.end(), 0, std::plus());
    // int dist = *std::ranges::max_element(mask);
    // int dist = 0;
    // for (const auto& v : mask) {
    //   dist += v;
    // }
    return dist;
  }
  struct State {
    std::vector<joltage_int> joltages;
    int presses;
    int dist;
    bool operator<(const State& other) const {
      // return dist > other.dist ||
      //        (dist == other.dist && presses > other.presses);
      return presses > other.presses ||
             (presses == other.presses && dist > other.dist);
    }
  };
  std::unordered_set<std::vector<joltage_int>, VectorHash> visited;
  int Fix() {
    // Precalc();
    std::vector<std::pair<int, int>> requirements_to_force;
    for (int i = 0; i < (int)joltage_requirements.size(); ++i) {
      for (int j = 0; j < (int)joltage_requirements.size(); ++j) {
        if (i == j) continue;
        if (joltage_requirements[i] <= joltage_requirements[j]) continue;
        requirements_to_force.emplace_back(i, j);
      }
    }
    std::vector<std::vector<int>> buttons_by_biggest;
    buttons_by_biggest.resize(joltage_requirements.size(), {});
    for (const auto& [i, b] : buttons | std::views::enumerate) {
      for (const int j : b.effect_pos) {
        buttons_by_biggest[j].push_back(i);
      }
    }

    std::queue<State> q;

    // const joltage_int smallest =
    // *std::ranges::min_element(joltage_requirements); std::vector<joltage_int>
    // hehe = joltage_requirements; for (auto& j : hehe) j -= smallest;

    q.emplace(joltage_requirements, 0, 1);
    int max_presses = 0;
    while (!q.empty()) {
      const auto [joltages, presses, dist] = q.front();
      q.pop();
      if (dist == 0) {
        return presses;
      }
      if (presses > max_presses) {
        max_presses = presses;
        // std::println("max_presses: {}", max_presses);
        // std::fflush(stdout);
      }

      auto [_, inserted] = visited.emplace(joltages);
      if (!inserted) continue;
      while (visited.size() > (int)7e7) {
        visited.erase(visited.begin());
      }

      // const int biggest_pos =
      //     std::ranges::max_element(joltages) - joltages.begin();
      const int biggest_pos = [&]() {
        joltage_int b = 1000;
        int bi = -1;
        for (const auto& [i, v] : joltages | std::views::enumerate) {
          if (v > 0 && v < b) b = v, bi = i;
        }
        assert(bi != -1);
        return bi;
      }();
      // for (const auto& b : buttons) {
      //   if (b.effect[biggest_pos] == '.') continue;
      for (const auto& bi : buttons_by_biggest[biggest_pos]) {
        const auto& b = buttons[bi];
        const std::vector<joltage_int> new_joltages = b.Press(joltages);

        // const bool valid = [&]() {
        //   for (const auto& [i, j] : requirements_to_force) {
        //     if (new_joltages[i] + 1 < new_joltages[j]) return false;
        //   }
        //   return true;
        // }();
        // if (!valid) continue;

        if (std::ranges::contains(new_joltages, -1)) continue;
        if (visited.contains(new_joltages)) continue;
        q.emplace(new_joltages, presses + 1, DistFrom(new_joltages));
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
    std::format_to(ctx.out(), "{}", m.light_requirements);
    std::format_to(ctx.out(), " | {}",
                   m.buttons | std::views::transform([](const Button& b) {
                     return std::format("{}", b);
                   }) | std::views::join_with(' ') |
                       std::ranges::to<std::string>());
    return std::format_to(ctx.out(), " | {}", m.joltage_requirements);
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
