#include <bits/stdc++.h>
#define lli long long int

const int kInf = std::numeric_limits<int>::max();
const int kGroupCount = 3;

struct Sleigh {
  std::vector<int> packages;
  const int n;
  const int target_sum;
  const int all_mask;
  Sleigh(std::istringstream&& sin)
      : packages([&]() {
          std::vector<int> ps;
          for (int p; sin >> p;) ps.push_back(p);
          std::ranges::sort(ps);
          return ps;
        }()),
        n(packages.size()),
        target_sum(
            std::reduce(packages.begin(), packages.end(), 0, std::plus()) /
            kGroupCount),
        all_mask((1 << packages.size()) - 1) {}
  Sleigh(const std::string& str) : Sleigh(std::istringstream(str)) {}

  struct Solution {
    std::pair<int, lli> score;
    std::array<int, kGroupCount> picks;
    auto operator<=>(const Solution& other) const {
      if (score == other.score) return picks[0] <=> other.picks[0];
      // if (score == other.score) return picks <=> other.picks;
      return score <=> other.score;
    }
    bool operator==(const Solution& other) const {
      // return score == other.score && picks == other.picks;
      return score == other.score && picks[0] == other.picks[0];
    }
  };
  std::set<Solution> bests;
  std::pair<int, lli> curr, best;
  std::pair<int, lli> BestConfigurationRec(
      const int start = 0, const int mask = 0, const int gi = 0,
      const int sum = 0, std::array<int, kGroupCount> picks = {0, 0, 0}) {
    if (gi == kGroupCount - 1) {
      picks[gi] = ~mask & all_mask;
      bests.emplace(curr, picks);
      while ((int)bests.size() > 10) bests.erase(std::prev(bests.end()));
      best = curr;
      return curr;
    }
    if (sum == target_sum) {
      if (gi == 0) {
        curr = {std::popcount((uint)mask), 1LL};
        for (int i = 0; i < n; ++i) {
          if (~mask & (1 << i)) continue;
          curr.second *= packages[i];
        }
        if (curr >= best) return {kInf, kInf};
      }
      return BestConfigurationRec(/*start=*/0, mask, gi + 1, /*sum=*/0, picks);
    }

    std::pair<int, lli> ans{kInf, kInf};
    const int before = picks[gi];
    for (int i = start; i < n; ++i) {
      if (mask & (1 << i)) continue;
      const int pi = packages[i];
      if (sum + pi > target_sum) continue;
      picks[gi] |= 1 << i;
      ans = std::min(ans, BestConfigurationRec(i + 1, mask | (1 << i), gi,
                                               sum + pi, picks));
      picks[gi] = before;
    }
    return ans;
  }

  lli BestConfiguration() {
    std::println("BestConfiguration:");
    // while (!bests.empty()) bests.pop();
    bests.clear();
    best = {kInf, kInf};
    const auto [min_items, qe] = BestConfigurationRec();
    std::println("\tmin_items: {} | qe: {}", min_items, qe);
    std::println("\tbest_configurations:");
    while (!bests.empty()) {
      // const auto [cnt_qe, picks] = bests.top();
      const auto [cnt_qe, picks] = *bests.rbegin();
      const auto [cnt, qe] = cnt_qe;
      // bests.pop();
      bests.erase(std::prev(bests.end()));
      std::println(
          "\t\t{} {} | {}", cnt, qe,
          picks | std::views::transform([&](const int m) {
            std::vector<int> ps;
            for (const auto [i, pi] : packages | std::views::enumerate) {
              if (m & (1 << i)) ps.push_back(pi);
            }
            return std::format("{}", ps);
          }) | std::views::join_with(std::string_view(" | ")) |
              std::ranges::to<std::string>());
    }
    return qe;
  }
};
template <>
struct std::formatter<Sleigh> {
  constexpr auto parse(std::format_parse_context& ctx) { return ctx.begin(); }
  template <class FormatContext>
  auto format(const Sleigh& s, FormatContext& ctx) const {
    return std::format_to(ctx.out(), "packages ({}): {} = {}\ntarget: {}", s.n,
                          s.packages, s.target_sum * kGroupCount, s.target_sum);
  }
};

int main() {
  const std::string input(std::istreambuf_iterator<char>(std::cin), {});
  Sleigh sleigh(input);

  std::println("sleigh:\n{}", sleigh);

  const lli ans = sleigh.BestConfiguration();
  std::println("ans: {}", ans);

  return 0;
}
