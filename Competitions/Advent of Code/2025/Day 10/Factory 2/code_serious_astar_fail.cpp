#include <bits/stdc++.h>
#define lli long long int
#define MOD3_PRUNE if (0)
#define MOD5_PRUNE if (0)

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
  std::vector<std::vector<std::reference_wrapper<const Button>>>
      buttons_by_joltage;
  int joltage_requirements_parity_mask;

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

    buttons_by_joltage.resize(joltage_requirements.size(), {});
    for (const auto& b : buttons) {
      for (const auto pos : b.effect_pos) {
        buttons_by_joltage[pos].emplace_back(b);
      }
    }
    FindAllStarts();

    Precalc();
  }
  Machine(const std::string& machine_str)
      : Machine(std::istringstream(machine_str)) {}

  struct MetaButton {
    std::reference_wrapper<const Button> button;
    std::vector<int> joltage_positions_to_zero;
  };
  std::vector<MetaButton> meta_buttons;
  int Dfs(std::vector<joltage_int> joltages, const int i = 0) {
    if (i == meta_buttons.size()) {
      // assert(*std::ranges::max_element(joltages) == 0);
      return 1;
    }
    const std::vector<int>& joltage_positions_to_zero =
        meta_buttons[i].joltage_positions_to_zero;
    const Button& b = meta_buttons[i].button;
    auto Next = [&](const std::vector<joltage_int>& next_joltages,
                    const int next_i) -> int {
      // if (*std::ranges::min_element(next_joltages) < 0) return 0;
      for (const int joltage_i : joltage_positions_to_zero) {
        if (next_joltages[joltage_i] > 0) return 0;
      }
      return Dfs(next_joltages, next_i);
    };

    int ans = 0;
    ans = Next(joltages, i + 1);
    const joltage_int available_presses = [&]() {
      joltage_int available_presses = std::numeric_limits<joltage_int>::max();
      for (const int pos : b.effect_pos) {
        available_presses = std::min(available_presses, joltages[pos]);
      }
      return available_presses;
    }();
    for (int j = 0; j < available_presses; ++j) {
      b.PressSub(joltages);
      ans += Next(joltages, i + 1);
    }
    return ans;
  }

  void FindAllStarts() {
    std::vector<std::tuple<int, int, int>> buttons_by_joltage_order;
    buttons_by_joltage_order.reserve(buttons_by_joltage.size());
    for (const auto [i, bs] : buttons_by_joltage | std::views::enumerate) {
      buttons_by_joltage_order.emplace_back(
          (int)bs.size(), (int)joltage_requirements[i], (int)i);
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

    std::fflush(stdout);

    const int valid_states = Dfs(joltage_requirements);
    std::println("\t{}", valid_states);
  }

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
  std::vector<std::unordered_set<std::vector<joltage_int>, VectorHash>>
      reachable_mod3masks_by_available_buttons;
  std::vector<std::unordered_set<std::vector<joltage_int>, VectorHash>>
      reachable_mod5masks_by_available_buttons;
  void FillReachableModX(const int mod, const int positive_mask,
                         std::unordered_set<std::vector<joltage_int>,
                                            VectorHash>& visited_joltages,
                         std::vector<joltage_int> joltages, const int i = 0) {
    if (i == (int)buttons.size()) {
      visited_joltages.insert(joltages);
      return;
    }
    FillReachableModX(mod, positive_mask, visited_joltages, joltages, i + 1);
    const Button& b = buttons[i];
    if (std::popcount((uint)(b.effect_mask & positive_mask)) != b.effect_count)
      return;
    for (int j = 1; j < mod; ++j) {
      b.PressAdd(joltages);
      for (auto& joltage : joltages) joltage %= mod;
      FillReachableModX(mod, positive_mask, visited_joltages, joltages, i + 1);
    }
  }
  std::vector<std::unordered_set<std::vector<joltage_int>, VectorHash>>
      possible_small_joltages;
  void FillPossibleSmall(const int positive_mask,
                         std::vector<joltage_int> joltages, int i = 0) {
    if (i == (int)buttons.size()) {
      possible_small_joltages[positive_mask].insert(joltages);
      return;
    }
    FillPossibleSmall(positive_mask, joltages, i + 1);
    const Button& b = buttons[i];
    if (std::popcount((uint)(b.effect_mask & positive_mask)) != b.effect_count)
      return;
    for (int k = 0; k < 3; ++k) {
      b.PressAdd(joltages);
      FillPossibleSmall(positive_mask, joltages, i + 1);
    }
  }
  std::vector<std::vector<std::reference_wrapper<const Button>>>
      buttons_by_positive_mask;
  void Precalc() {
    const auto start = std::chrono::high_resolution_clock::now();

    joltage_requirements_parity_mask = 0;
    for (const auto [i, v] : joltage_requirements | std::views::enumerate) {
      joltage_requirements_parity_mask |= (v & 1) << i;
    }
    buttons_by_positive_mask.resize(1 << joltage_requirements.size(), {});

    reachable_mod2masks_by_available_buttons.resize(
        1 << joltage_requirements.size(),
        std::vector<bool>(1 << joltage_requirements.size(), false));
    reachable_mod3masks_by_available_buttons.resize(
        1 << joltage_requirements.size(), {});
    reachable_mod5masks_by_available_buttons.resize(
        1 << joltage_requirements.size(), {});
    possible_small_joltages.resize(1 << joltage_requirements.size(), {});
    for (int positive_mask = 0, end = 1 << joltage_requirements.size();
         positive_mask < end; ++positive_mask) {
      FillReachableMod2(positive_mask);
      MOD3_PRUNE {
        FillReachableModX(
            3, positive_mask,
            reachable_mod3masks_by_available_buttons[positive_mask],
            std::vector<joltage_int>(joltage_requirements.size(), 0));
      }
      MOD5_PRUNE {
        FillReachableModX(
            5, positive_mask,
            reachable_mod5masks_by_available_buttons[positive_mask],
            std::vector<joltage_int>(joltage_requirements.size(), 0));
      }
      FillPossibleSmall(positive_mask, std::vector<joltage_int>(
                                           joltage_requirements.size(), 0));
      for (const auto& b : buttons) {
        if (b.effect_count !=
            std::popcount((uint)(b.effect_mask & positive_mask)))
          continue;
        buttons_by_positive_mask[positive_mask].emplace_back(b);
      }
    }
    const auto end = std::chrono::high_resolution_clock::now();
    const auto duration =
        std::chrono::duration_cast<time_precision>(end - start);
    std::println("Precalc: {}", duration);
  }

  int ForceBiggestImpactButtons(std::vector<joltage_int> joltages,
                                const int positive_mask) {
    auto GetJoltagesMask = [&]() {
      int mask = 0;
      for (const auto [i, v] : joltages | std::views::enumerate) {
        mask |= (v > 0) << i;
      }
      return mask;
    };
    int joltages_mask = GetJoltagesMask();
    auto FindBiggestImpactButton = [&]() {
      auto best_impact = std::make_pair(-kInf, -kInf);
      auto best_positive_impact = -kInf;
      const Button* best = nullptr;  //, *best_positive = nullptr;
      for (const Button& b : buttons_by_positive_mask[positive_mask]) {
        const int effect = std::popcount((uint)(b.effect_mask & joltages_mask));
        if (effect == 0) continue;
        const auto impact = std::make_pair(effect, -(b.effect_count - effect));
        // const auto impact = std::make_pair(-(b.effect_count - effect),
        // effect);
        if (impact > best_impact) {
          best = &b, best_impact = impact;
        }
        // if (effect == b.effect_count && effect > best_positive_impact)
        //   best_positive = &b, best_positive_impact = effect;
      }
      return best;
      // return best_positive == nullptr ? best : best_positive;
    };
    const Button* b = FindBiggestImpactButton();
    int presses = 0;
    while (std::popcount((uint)joltages_mask)) {
      joltage_int delta = std::numeric_limits<joltage_int>::max();
      for (const int pos : b->effect_pos) {
        if (joltages[pos] <= 0) continue;
        delta = std::min(delta, joltages[pos]);
      }
      for (const int pos : b->effect_pos) joltages[pos] -= delta;
      presses += delta;
      // joltages = b->Press(joltages);
      // ++presses;
      const int new_joltages_mask = GetJoltagesMask();
      if (joltages_mask == new_joltages_mask) continue;
      joltages_mask = new_joltages_mask;
      b = FindBiggestImpactButton();
    }
    // const int negative_count = std::ranges::count_if(
    //     joltages, [](const int joltage) { return joltage < 0; });
    auto negative_joltages_view =
        joltages |
        std::views::filter([](const int joltage) { return joltage < 0; });
    const int negative_penalty =
        -std::reduce(negative_joltages_view.begin(),
                     negative_joltages_view.end(), 0, std::plus());
    return presses + negative_penalty;
    // return presses;
  }

  int RecTryMinimizingPressesUsingButtonsCoveringEverything(
      const std::vector<joltage_int>& initial_joltages, const int positive_mask,
      std::vector<joltage_int> deltas, int i = 0, int used_buttons = 0) {
    if (i == buttons_by_positive_mask[positive_mask].size()) {
      if (*std::ranges::min_element(deltas) == 0) return kInf;
      int presses = 0, negative_penalty = 0;
      for (const auto [req, delta] :
           std::views::zip(initial_joltages, deltas)) {
        const joltage_int min_presses = req / delta + req % delta != 0;
        const joltage_int final_delta = delta * min_presses;
        presses = std::max(presses, (int)min_presses);
        negative_penalty += final_delta - req;
      }
      return presses + negative_penalty;
    }

    int ans = RecTryMinimizingPressesUsingButtonsCoveringEverything(
        initial_joltages, positive_mask, deltas, i + 1, used_buttons);
    const Button& b = buttons_by_positive_mask[positive_mask][i];
    b.PressAdd(deltas);
    ans = std::min(ans, RecTryMinimizingPressesUsingButtonsCoveringEverything(
                            initial_joltages, positive_mask, deltas, i + 1,
                            used_buttons + 1));

    return ans;
  }
  int TryMinimizingPressesUsingButtonsCoveringEverything(
      const std::vector<joltage_int>& initial_joltages,
      const int positive_mask) {
    return RecTryMinimizingPressesUsingButtonsCoveringEverything(
        initial_joltages, positive_mask,
        std::vector<joltage_int>(joltage_requirements.size(), 0));
  }

  int TryMinimizingNegativePenalty(
      const std::vector<joltage_int>& initial_joltages,
      const int positive_mask) {
    std::priority_queue<State, std::vector<State>, std::greater<State>> pq;
    std::unordered_set<std::vector<joltage_int>, VectorHash> hehe;
    pq.emplace(initial_joltages,
               std::reduce(initial_joltages.begin(), initial_joltages.end(), 0,
                           std::plus()),
               0, 0);
    while (!pq.empty()) {
      const auto [joltages, joltage_sum, presses, h] = pq.top();
      pq.pop();

      if (joltage_sum == 0) return h;

      if (const bool inserted = hehe.insert(joltages).second; !inserted) {
        continue;
      }

      for (const Button& b : buttons_by_positive_mask[positive_mask]) {
        const auto new_joltages = b.Press(joltages);
        int new_joltage_sum = 0, negative_sum = 0;
        for (const auto& joltage : new_joltages) {
          if (joltage > 0)
            new_joltage_sum += joltage;
          else
            negative_sum += joltage;
        }
        pq.emplace(new_joltages, new_joltage_sum, presses + 1,
                   presses + -negative_sum);
      }
    }
    return kInf;
  }

  struct State {
    std::vector<joltage_int> joltages;
    joltage_int joltage_sum;
    joltage_int presses;
    // int h;
    // int f() const { return presses + h; }
    // auto operator<=>(const State& other) const { return f() <=> other.f(); }
    joltage_int f;
    // auto operator<=>(const State& other) const { return f <=> other.f; }
    auto operator<=>(const State& other) const {
      return f <=> other.f;
      // return f == other.f ? (joltage_sum == other.joltage_sum
      //                            ? joltages <=> other.joltages
      //                            : joltage_sum <=> other.joltage_sum)
      //                     : f <=> other.f;
      // return f == other.f ? *std::ranges::max_element(joltages) -
      //                               *std::ranges::min_element(joltages) <=>
      //                           *std::ranges::max_element(other.joltages) -
      //                               *std::ranges::min_element(other.joltages)
      //                     : f <=> other.f;
      // return f == other.f ? *std::ranges::max_element(joltages) <=>
      //                           *std::ranges::max_element(other.joltages)
      //                     : f <=> other.f;
      // return f == other.f ? *std::ranges::min_element(other.joltages) <=>
      //                           *std::ranges::min_element(joltages)
      //                     : f <=> other.f;
    }

    // auto operator==(const State& other) const {
    //   return presses == other.presses && joltage_sum == other.joltage_sum &&
    //          joltages == other.joltages;
    // }
    // TODO: implement operator== if needed
  };
  std::unordered_map<std::vector<joltage_int>, int, VectorHash> best_memo;
  // std::set<std::pair<int, std::vector<joltage_int>>> visited;
  std::unordered_set<std::vector<joltage_int>, VectorHash> visited;
  // A* to find the minimum amount of presses.
  int astar_iterations;
  int AstarFix() {
    astar_iterations = 0;
    std::priority_queue<State, std::vector<State>, std::greater<State>> pq;
    auto Enqueue = [&](const std::vector<joltage_int>& joltages,
                       const int joltage_sum, const int presses) {
      if (std::ranges::find_if(joltages, [](const joltage_int joltage) {
            return joltage < 0;
          }) != joltages.end())
        return false;
      // if (std::ranges::contains(joltages, -1)) return false;
      if (visited.contains(joltages)) return false;
      const auto [positive_mask, parity_mask, mod3_mask, mod5_mask] = [&]() {
        int positive_mask = 0, parity_mask = 0;
        std::vector<joltage_int> mod3_mask(joltage_requirements.size());
        std::vector<joltage_int> mod5_mask(joltage_requirements.size());
        for (const auto [i, v] : joltages | std::views::enumerate) {
          positive_mask |= (v > 0) << i;
          parity_mask |= (v & 1) << i;
          mod3_mask[i] = v % 3;
          mod5_mask[i] = v % 5;
        }
        return std::make_tuple(positive_mask, parity_mask, mod3_mask,
                               mod5_mask);
      }();
      const bool has_buttons_to_finish = [&]() {
        int effect_mask = 0;
        for (const Button& b : buttons_by_positive_mask[positive_mask]) {
          effect_mask |= b.effect_mask;
        }
        return (positive_mask & effect_mask) == positive_mask;
      }();
      if (!has_buttons_to_finish) return false;

      if (!reachable_mod2masks_by_available_buttons[positive_mask][parity_mask])
        return false;
      MOD3_PRUNE {
        if (!reachable_mod3masks_by_available_buttons[positive_mask].contains(
                mod3_mask))
          return false;
      }
      MOD5_PRUNE {
        if (!reachable_mod5masks_by_available_buttons[positive_mask].contains(
                mod5_mask))
          return false;
      }

      const joltage_int heuristic =
          ForceBiggestImpactButtons(joltages, positive_mask);
      // const joltage_int heuristic =
      //     presses > 80
      //         ? TryMinimizingNegativePenalty(joltages, positive_mask)
      //         : ForceBiggestImpactButtons(joltages, positive_mask);
      // const joltage_int heuristic =
      //     ForceBiggestImpactButtons(joltages, positive_mask) +
      //     TryMinimizingPressesUsingButtonsCoveringEverything(joltages,
      //                                                        positive_mask);
      // const joltage_int heuristic =
      //     TryMinimizingNegativePenalty(joltages, positive_mask);
      // const joltage_int heuristic = joltage_sum;
      std::vector<joltage_int> hehe = joltages;
      // std::ranges::sort(hehe);
      int hehe_deltas = 0;
      for (int i = 0, j = (int)hehe.size(); i < j; ++i, --j) {
        hehe_deltas += std::abs(hehe[j] - hehe[i]);
      }
      pq.emplace(joltages, joltage_sum, presses,
                 /*f=*/
                 (presses + /*h=*/heuristic + hehe_deltas));
      return true;
    };
    Enqueue(joltage_requirements,
            std::reduce(joltage_requirements.begin(),
                        joltage_requirements.end(), 0, std::plus()),
            0);
    auto best = std::make_pair(0, -(int)1e6);
    while (!pq.empty()) {
      const auto [joltages, joltage_sum, presses, _] = pq.top();
      pq.pop();
      if (auto curr = std::make_pair(presses, -joltage_sum); curr > best) {
        best = curr;
        std::println("{} {} | it {:.3e} | pq {:.3e} | {}", presses, joltage_sum,
                     (double)astar_iterations, (double)pq.size(), joltages);
      }
      std::fflush(stdout);

      if (joltage_sum == 0) return presses;

      if (const bool inserted = visited.emplace(joltages).second; !inserted)
        continue;
      while (visited.size() > 2e7) {
        visited.erase(visited.begin());
      }

      ++astar_iterations;

      const int positive_mask = [&]() {
        int positive_mask = 0;
        for (const auto [i, v] : joltages | std::views::enumerate) {
          positive_mask |= (v > 0) << i;
        }
        return positive_mask;
      }();
      for (const Button& b : buttons_by_positive_mask[positive_mask]) {
        Enqueue(b.Press(joltages), joltage_sum - b.effect_count, presses + 1);
      }

      if (presses == 0) continue;
      std::vector<joltage_int> delta = joltage_requirements;
      for (auto [d, joltage] : std::views::zip(delta, joltages)) {
        d -= joltage;
      }
      for (int k = 2; k <= 2; ++k) {
        std::vector<joltage_int> new_joltages = joltage_requirements;
        bool valid = true;
        for (auto [new_joltage, d] : std::views::zip(new_joltages, delta)) {
          const int to_sub = (int)d * k;
          if (to_sub > new_joltage) {
            valid = false;
            break;
          }
          new_joltage -= to_sub;
        }
        if (!valid) break;
        Enqueue(new_joltages,
                std::reduce(new_joltages.begin(), new_joltages.end(), 0,
                            std::plus()),
                presses * k);
        // if (!Enqueue(new_joltages,
        //              std::reduce(new_joltages.begin(), new_joltages.end(),
        // 0,
        //                          std::plus()),
        //              presses * k))
        //   break;
      }
    }
    assert(false);
    return -1;
  }
  int RecFix(const int bi, const int bj,
             const std::vector<joltage_int> joltages, const int joltage_sum) {
    return -1;
    // if (joltage_sum == 0) {
    //   return 0;
    // }
    // if (bi == -1) {
    //   return kInf;
    // }
    // if (bj >= (int)buttons_by_effect_count[bi].size())
    //   return RecFix(bi - 1, 0, joltages, joltage_sum);

    // const Button& b = buttons_by_effect_count[bi][bj];
    // std::vector<std::pair<int, std::vector<joltage_int>>> hehe;
    // for (int p = 1;; ++p) {
    //   const std::vector<joltage_int> new_joltages =
    //       b.Press(p == 1 ? joltages : hehe.back().second);
    //   if (std::ranges::contains(new_joltages, -1)) break;
    //   hehe.emplace_back(p, new_joltages);
    // }

    // int ans = kInf;
    // const auto Next = [&](const std::vector<joltage_int>& new_joltages,
    //                       const int new_joltage_sum) {
    //   return RecFix(bi, bj + 1, new_joltages, new_joltage_sum);
    // };
    // for (const auto& [p, new_joltages] : hehe | std::views::reverse) {
    //   const int next_res =
    //       p + Next(new_joltages, joltage_sum - p * b.effect_count);
    //   if (next_res < kInf) {
    //     std::println("pressed {} x {} times", b, p);
    //     return next_res;
    //   }
    // }
    // return Next(joltages, joltage_sum);
  }
  int Fix() {
    // return RecFix((int)buttons_by_effect_count.size() - 1, 0,
    //               joltage_requirements,
    //               std::reduce(joltage_requirements.begin(),
    //                           joltage_requirements.end(), 0, std::plus()));
    return AstarFix();
  }
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
    std::format_to(ctx.out(), "{} | [{}]", mini,
                   m.buttons_by_joltage | std::views::enumerate |
                       std::views::transform([&](const auto& ibs) {
                         const auto [i, bs] = ibs;
                         return std::format(
                             "({}, {})", m.joltage_requirements[i], bs.size());
                       }) |
                       std::views::join_with(std::string_view(", ")) |
                       std::ranges::to<std::string>());
    // std::format_to(ctx.out(), "{}",
    //                m.buttons | std::views::transform([](const Button& b) {
    //                  return std::format("{}", b);
    //                }) | std::views::join_with(' ') |
    //                    std::ranges::to<std::string>());
    // std::format_to(ctx.out(), " | {}", m.joltage_requirements);
    // std::format_to(
    //     ctx.out(), " | [{}]",
    //     m.buttons_by_joltage |
    //         std::views::transform(
    //             [](const std::vector<std::reference_wrapper<const Button>>&
    //                    bs) { return std::format("{}", bs.size()); }) |
    //         std::views::join_with(std::string_view(", ")) |
    //         std::ranges::to<std::string>());
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

  // const int ans = factory.Fix();
  // std::println("Ans: {}", ans);

  return 0;
}
