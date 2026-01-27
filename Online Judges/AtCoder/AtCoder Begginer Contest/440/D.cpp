#include <bits/stdc++.h>
#define DEBUG if (0)
#define lli long long int
#define ldouble long double

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
    const int bigger_than_x_inside_start_range = start_range.hi - x + 1;
    int hi = (int)missing_ranges.size() - 1;
    while (lo < hi) {
      const int mid = (lo + hi) >> 1;
      const Range& r = missing_ranges[mid];
      const int reachable =
          start_range.lo == r.lo
              ? r.Size() - 1
              : r.before_acc - start_range.before_acc +
                    (r.Size() - 1 - bigger_than_x_inside_start_range);
      if (reachable >= y)
        hi = mid;
      else
        lo = mid + 1;
    }
    return lo;
  }
  int YthSmallestAtLeastX(const int x, const int y) {
    const int start_range_pos = FindStartRangePos(x);
    const Range& start_range = missing_ranges[start_range_pos];
    std::println("\t{} {} | {} || {}", x, y, start_range_pos,
                 start_range.ToString());
    std::fflush(stdout);
    assert(start_range.hi >= x);
    const int range_pos = FindRangePos(start_range_pos, x, y);
    const Range& target_range = missing_ranges[range_pos];
    std::println("\t{} {} | {} || {}", x, y, range_pos,
                 target_range.ToString());
    std::fflush(stdout);
    // assert(target_range.before_acc - start_range.before_acc +
    //            target_range.Size() - 1 >=
    //        y);
    const int before = (target_range.before_acc - start_range.before_acc) -
                       (start_range.hi - x + 1);
    const int offset = start_range.lo == target_range.lo
                           ? (x > start_range.lo ? y + (x - start_range.lo) : 0)
                           : (y - before - 1);
    std::println("\tbefore {} | offset {}", before, offset);
    const int ans = target_range.lo + offset;
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

    int sum = 0;
    for (int i = 1; i < (int)missing_ranges.size(); ++i) {
      missing_ranges[i].before_acc =
          missing_ranges[i - 1].before_acc + missing_ranges[i - 1].Size();
    }

    for (const auto& mr : missing_ranges) {
      std::println("{}", mr.ToString());
    }

    for (int qi = 0; qi < q; ++qi) {
      int x, y;
      std::cin >> x >> y;
      --y;
      const int ans = YthSmallestAtLeastX(x, y);
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
