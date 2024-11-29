#include <bits/stdc++.h>
#define DEBUG if (0)
#define lli long long int
#define ldouble long double

struct TestCase {
  int n, q;
  std::string s;

  std::vector<std::vector<int>> acc;
  std::vector<int> slashes;
  std::vector<int> nums;
  int GetRangeSum(const int kind, const int lo, const int hi) {
    if (lo > hi) return 0;
    return acc[kind][hi + 1] - acc[kind][lo];
  }
  std::pair<int, int> Evaluate(const int pos, const int lo, const int hi) {
    const int ones = GetRangeSum(0, lo, pos - 1),
              twos = GetRangeSum(1, pos, hi);
    return std::make_pair(2 * std::min(ones, twos) + 1, std::abs(twos - ones));
  }
  void Solve() {
    acc.resize(2, std::vector<int>(n + 1, 0));
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < 2; ++j) {
        acc[j][i + 1] = acc[j][i] + (s[i] - '1' == j);
      }
    }
    for (int i = 0; i < n; ++i) {
      if (s[i] == '/') {
        slashes.push_back(i);
      } else {
        nums.push_back(i);
      }
    }

    for (int qq = 0; qq < q; ++qq) {
      int range_lo, range_hi;
      std::cin >> range_lo >> range_hi;
      --range_lo, --range_hi;

      DEBUG for (auto loit =
                     std::lower_bound(nums.begin(), nums.end(), range_lo);
                 loit != nums.end() && *loit <= range_hi; ++loit) {
        std::cout << "i: " << *loit
                  << " | res: " << Evaluate(*loit, range_lo, range_hi).second
                  << "\n";
      }

      auto Eval = [&](const int i, const int get_res = false) {
        const auto [res, sum] = Evaluate(i, range_lo, range_hi);
        return get_res ? res : sum;
      };

      int lo = -1, hi = -1;
      if (nums.empty()) {
        std::cout << "1\n";
        continue;
      } else {
        auto loit = std::lower_bound(nums.begin(), nums.end(), range_lo);
        if (loit == nums.end() || *loit > range_hi) {
          std::cout << "1\n";
          continue;
        }
        auto hiit = std::upper_bound(nums.begin(), nums.end(), range_hi);
        lo = loit - nums.begin(), hi = std::prev(hiit) - nums.begin();
        auto Valid = [&](const int i) {
          return i >= 0 && i < (int)nums.size() && nums[i] >= range_lo &&
                 nums[i] <= range_hi;
        };
        assert(Valid(lo) && Valid(hi));
      }
      assert(lo != -1 && hi != -1);

      while (hi - lo > 3) {
        DEBUG std::cout << "lo, hi: " << lo << " " << hi << "\n";
        int midlo = std::floor((double)(2 * lo + hi) / 3),
            midhi = std::ceil((double)(lo + 2 * hi) / 3);
        const int elo = Eval(nums[midlo]), ehi = Eval(nums[midhi]);
        DEBUG std::cout << "\tmidlo " << midlo << " | elo " << elo << "\n";
        DEBUG std::cout << "\tmidhi " << midhi << " | ehi " << ehi << "\n";
        if (elo <= ehi) hi = midhi;
        if (ehi <= elo) lo = midlo;
      }
      std::pair<int, int> best_pos = std::make_pair(Eval(nums[lo]), nums[lo]);
      for (int i = lo + 1; i <= hi; ++i)
        best_pos = std::min(best_pos, std::make_pair(Eval(nums[i]), nums[i]));
      DEBUG std::cout << "best_pos: " << best_pos.first << " "
                      << best_pos.second << "\n";

      int ans = 0;
      if (!slashes.empty()) {
        auto hiit =
            std::lower_bound(slashes.begin(), slashes.end(), best_pos.second);
        auto Valid = [&](const int i) {
          return i >= range_lo && i <= range_hi;
        };
        if (hiit != slashes.end() && Valid(*hiit)) {
          DEBUG std::cout << "nxt: " << *hiit << "\n";
          ans = Eval(*hiit, /*get_res=*/true);
        }
        auto loit = std::prev(hiit);
        if (loit != slashes.end() && Valid(*loit)) {
          DEBUG std::cout << "prv: " << *loit << "\n";
          ans = std::max(ans, Eval(*loit, /*get_res=*/true));
        }
      }

      std::cout << ans << "\n";
    }
  }

  bool Run() {
    if (!(std::cin >> n >> q)) return false;
    std::cin >> s;

    Solve();

    return true;
  }
};
TestCase test_case;

int main() {
  // int test_cases;
  // std::cin >> test_cases;
  // for (int t = 1; t <= test_cases; ++t) {
  //   test_case = TestCase{};
  //   test_case.Run();
  // }

  do {
    test_case = TestCase{};
  } while (test_case.Run());

  return 0;
}
