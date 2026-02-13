#include <bits/stdc++.h>
#define DEBUG if (0)
#define lli long long int
#define ldouble long double

/*
Problem:
Given `n` numbers, process `q` queries.
Every query asks to find the yth missing number >= x.

Solution:
Using accumulated sums, we can answer each query with 2 binary searches.
1. Find the "missing range" which contains `x`;
2. Find the first "missing range" which had `y` elements after `x`.
It's a bit convoluted and has a couple corner cases. But it's an interesting
problem to think about.
*/

struct TestCase {
  int n, q;
  std::vector<int> a;

  struct Range {
    int lo, hi;
    int before_acc;
    int Size() const { return hi - lo + 1; }
    std::string ToString() const {
      return std::format("{} {} | {}", lo, hi, before_acc);
    }
  };
  std::vector<Range> missing_ranges;

  int FindStartRangePos(const int x) {
    int lo = 0, hi = (int)missing_ranges.size() - 1;
    while (lo < hi) {
      const int mid = (lo + hi) >> 1;
      const Range& r = missing_ranges[mid];
      if (r.hi >= x)
        hi = mid;
      else
        lo = mid + 1;
    }
    return lo;
  }
  int FindRangePos(int lo, const int x, const int y) {
    const Range& start_range = missing_ranges[lo];
    const int bigger_than_x_inside_start_range =
        start_range.hi - std::max(x, start_range.lo) + 1;
    int hi = (int)missing_ranges.size() - 1;
    while (lo < hi) {
      const int mid = (lo + hi) >> 1;
      const Range& r = missing_ranges[mid];
      const int cnt =
          bigger_than_x_inside_start_range +
          (start_range.lo == r.lo
               ? 0
               : (r.Size() + (r.before_acc - start_range.before_acc -
                              start_range.Size())));
      DEBUG { std::println("\t\t{} | {} | cnt {}", mid, r.ToString(), cnt); }
      if (cnt > y)
        hi = mid;
      else
        lo = mid + 1;
    }
    return lo;
  }
  int YthSmallestAtLeastX(const int x, const int y) {
    DEBUG {
      std::println("\tx {} y {}", x, y);
      std::fflush(stdout);
    }
    const int start_range_pos = FindStartRangePos(x);
    const Range& start_range = missing_ranges[start_range_pos];
    DEBUG {
      std::println("\t{} | start_range {}", start_range_pos,
                   start_range.ToString());
      std::fflush(stdout);
    }
    assert(start_range.hi >= x);
    const int target_range_pos = FindRangePos(start_range_pos, x, y);
    const Range& target_range = missing_ranges[target_range_pos];
    DEBUG {
      std::println("\t{} | target_range {}", target_range_pos,
                   target_range.ToString());
      std::fflush(stdout);
    }
    const int before =
        start_range_pos == target_range_pos
            ? 0
            : (start_range.hi - std::max(x, start_range.lo) + 1) +
                  (target_range.before_acc - start_range.before_acc -
                   start_range.Size());
    const int offset = y - before;
    DEBUG {
      std::println("\tbefore {} | offset {}", before, offset);
      std::fflush(stdout);
    }
    const int ans = start_range_pos == target_range_pos && x >= target_range.lo
                        ? x + offset
                        : target_range.lo + offset;
    return ans;
  }

  bool Run() {
    if (!(std::cin >> n >> q)) return false;
    a.resize(n);
    for (auto& ai : a) std::cin >> ai;
    std::ranges::sort(a);

    if (a[0] != 1) {
      missing_ranges.emplace_back(1, a[0] - 1, 0);
    }
    for (int i = 1; i < n; ++i) {
      if (a[i - 1] + 1 == a[i]) continue;
      missing_ranges.emplace_back(a[i - 1] + 1, a[i] - 1, 0);
    }
    missing_ranges.emplace_back(a.back() + 1, std::numeric_limits<int>::max(),
                                0);

    for (int i = 1; i < (int)missing_ranges.size(); ++i) {
      missing_ranges[i].before_acc =
          missing_ranges[i - 1].before_acc + missing_ranges[i - 1].Size();
    }

    DEBUG for (const auto& mr : missing_ranges) {
      std::println("{}", mr.ToString());
    }

    // std::vector<int> missing_numbers;
    // for (const auto& mr : missing_ranges) {
    //   for (int i = mr.lo; i <= std::min(60, mr.hi); ++i) {
    //     missing_numbers.push_back(i);
    //   }
    // }
    // for (int x = 1; x < 20; ++x) {
    //   for (int y = 1; y < 20; ++y) {
    //     const int ans = YthSmallestAtLeastX(x, y - 1);
    //     const int cor = [&]() {
    //       auto it = std::ranges::lower_bound(missing_numbers, x);
    //       return *std::next(it, y - 1);
    //     }();
    //     if (ans != cor) {
    //       std::println("{} {} | ans {} cor {}", x, y, ans, cor);
    //     }
    //   }
    // }

    for (int qi = 0; qi < q; ++qi) {
      int x, y;
      std::cin >> x >> y;
      const int ans = YthSmallestAtLeastX(x, y - 1);
      std::println("{}", ans);
    }

    return true;
  }
};
TestCase test_case;

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  do {
    test_case = TestCase{};
  } while (test_case.Run());

  return 0;
}
