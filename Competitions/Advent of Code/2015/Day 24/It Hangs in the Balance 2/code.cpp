#include <bits/stdc++.h>
#define lli long long int

const int kInf = std::numeric_limits<int>::max();
const int kGroupCount = 4;

struct Sleigh {
  std::vector<int> packages;
  const int n;
  const int target_sum;
  const uint all_mask;
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
    std::array<uint, kGroupCount> picks;
    auto operator<=>(const Solution& other) const {
      // if (score == other.score) return picks <=> other.picks;
      if (score == other.score) return picks[0] <=> other.picks[0];
      return score <=> other.score;
    }
    bool operator==(const Solution& other) const {
      // return score == other.score && picks == other.picks;
      return score == other.score && picks[0] == other.picks[0];
    }
  };
  std::set<Solution> bests;
  std::pair<int, lli> curr, best;
  std::array<uint, kGroupCount> curr_picks = {0, 0, 0};
  std::pair<int, lli> BestConfigurationRec(const int start = 0,
                                           const uint mask = 0,
                                           const int gi = 0,
                                           const int sum = 0) {
    if (gi == kGroupCount - 1) {
      curr_picks[gi] = ~mask & all_mask;
      bests.emplace(curr, curr_picks);
      while ((int)bests.size() > 10) bests.erase(std::prev(bests.end()));
      best = curr;
      return curr;
    }
    if (sum == target_sum) {
      if (gi == 0) {
        curr = {std::popcount(mask), 1LL};
        for (int i = std::countr_zero(mask); i < n;
             i += std::countr_zero(mask >> (i + 1)) + 1) {
          assert(mask & (1 << i));
          curr.second *= packages[i];
        }
        if (curr >= best) return {kInf, kInf};
      }
      return BestConfigurationRec(/*start=*/std::countr_one(mask), mask, gi + 1,
                                  /*sum=*/0);
    }

    std::pair<int, lli> ans{kInf, kInf};
    const int before = curr_picks[gi];
    for (int i = start, end = gi > 0 && sum == 0 ? start + 1 : n; i < end;
         i += std::countr_one(mask >> (i + 1)) + 1) {
      assert(i >= 0 && i < n);
      assert(~mask & (1 << i));
      const int pi = packages[i];
      if (sum + pi > target_sum) break;
      curr_picks[gi] |= 1 << i;
      ans = std::min(
          ans, BestConfigurationRec(i + std::countr_one(mask >> (i + 1)) + 1,
                                    mask | (1 << i), gi, sum + pi));
      curr_picks[gi] = before;
    }
    return ans;
  }

  lli BestConfiguration() {
    std::println("BestConfiguration:");
    bests.clear();
    best = {kInf, kInf};
    curr_picks = {0, 0, 0};
    const auto [min_items, qe] = BestConfigurationRec();
    std::println("\tmin_items: {} | qe: {}", min_items, qe);
    std::println("\tbest_configurations:");
    while (!bests.empty()) {
      const auto [cnt_qe, picks] = *bests.rbegin();
      const auto [cnt, qe] = cnt_qe;
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
