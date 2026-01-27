#include <bits/stdc++.h>
#define lli long long int

// This was the first day where I stopped to optimize it.
// It was also the first time I optimized the range intersection to O(n*lg).
// It's pretty interesting.

struct Range {
  lli start, end;
  Range(std::istream&& sin)
      : start([&]() {
          lli s;
          sin >> s;
          sin.ignore(std::numeric_limits<std::streamsize>::max(), '-');
          return s;
        }()),
        end([&]() {
          lli e;
          sin >> e;
          return e;
        }()) {}
  Range(const std::string& range_str) : Range(std::istringstream(range_str)) {}
  Range(const lli start_, const lli end_) : start(start_), end(end_) {}
  auto operator<=>(const Range& other) const {
    return start == other.start ? end <=> other.end : start <=> other.start;
  }
  bool operator==(const Range& other) const {
    return start == other.start && end == other.end;
  }

  bool IsInside(const lli x) const { return x >= start && x <= end; }
};
template <>
struct std::formatter<Range> {
  constexpr auto parse(std::format_parse_context& ctx) { return ctx.begin(); }
  template <class FormatContext>
  auto format(const Range& r, FormatContext& ctx) const {
    return std::format_to(ctx.out(), "{}-{}", r.start, r.end);
  }
};

struct Cafeteria {
  std::vector<Range> fresh_ranges;
  std::vector<Range> compressed_fresh_ranges;

  friend std::istream& operator>>(std::istream& sin, Cafeteria& c) {
    c.fresh_ranges.clear();
    for (std::string line; std::getline(sin, line) && !line.empty();) {
      c.fresh_ranges.emplace_back(line);
    }
    std::ranges::sort(c.fresh_ranges);
    // c.CompressFreshRangesWithSets();
    c.CompressFreshRanges();
    return sin;
  }

  // This is O(n^2), we probably can make it in n*lg with sets
  // ~18.5s over 1e5 ranges ranges with no overlap
  void CompressFreshRangesNaive() {
    std::println("compressing");

    std::list<Range> ranges;
    // start is sorted, the ranges can only extend the end
    for (const auto& r : fresh_ranges) {
      Range to_add = r;
      for (auto it = ranges.begin(); it != ranges.end(); ++it) {
        if (!it->IsInside(r.start)) continue;
        to_add = {std::min(r.start, it->start), std::max(r.end, it->end)};
        ranges.erase(it);
        break;
      }
      if (std::ranges::contains(ranges, to_add)) continue;
      ranges.insert(std::ranges::lower_bound(ranges, to_add), to_add);
    }

    compressed_fresh_ranges = std::vector<Range>(ranges.begin(), ranges.end());
  }

  // O(n*lg) \o/
  // ~85ms over 1e5 ranges ranges with no overlap
  // I'm not sure what I was thinking here, but I clearly missed that I just
  // need to look at the last element hahaha.
  void CompressFreshRangesWithSets() {
    std::println("compressing");

    std::set<Range> ranges;
    // start is sorted, the ranges can only extend the end
    for (const auto& r : fresh_ranges) {
      Range to_add = r;

      auto start_it = ranges.lower_bound(to_add);
      if (!ranges.empty()) start_it = std::prev(start_it);
      for (auto it = start_it; it != ranges.end(); ++it) {
        if (!it->IsInside(r.start)) continue;
        if (it->end < r.start) break;
        to_add = {std::min(r.start, it->start), std::max(r.end, it->end)};
        ranges.erase(it);
        break;
      }
      if (ranges.contains(to_add)) continue;
      ranges.insert(to_add);
    }

    compressed_fresh_ranges = std::vector<Range>(ranges.begin(), ranges.end());
  }

  // O(n*lg) \o/
  // ~70ms over 1e5 ranges ranges with no overlap
  void CompressFreshRanges() {
    std::println("compressing");

    std::vector<Range> ranges;
    ranges.push_back(fresh_ranges[0]);
    // start is sorted, the ranges can only extend the end or be a new range.
    for (const auto& r : fresh_ranges | std::views::drop(1)) {
      if (Range& last_range = ranges.back(); r.start <= last_range.end)
        last_range.end = std::max(last_range.end, r.end);
      else
        ranges.push_back(r);
    }

    compressed_fresh_ranges = ranges;
  }

  lli FreshIngredientsCount() const {
    lli count = 0;
    for (const auto& r : compressed_fresh_ranges) {
      count += r.end - r.start + 1;
    }
    return count;
  }
};
template <>
struct std::formatter<Cafeteria> {
  constexpr auto parse(std::format_parse_context& ctx) { return ctx.begin(); }
  template <class FormatContext>
  auto format(const Cafeteria& c, FormatContext& ctx) const {
    std::format_to(ctx.out(), "\toriginal_ranges:\n");
    for (int i = 0; i < c.fresh_ranges.size(); ++i) {
      std::format_to(ctx.out(), "{}", c.fresh_ranges[i]);
      if (i + 1 != c.fresh_ranges.size()) std::format_to(ctx.out(), "\n");
    }
    std::format_to(ctx.out(), "\n\tcompressed_ranges:\n");
    for (int i = 0; i < c.compressed_fresh_ranges.size(); ++i) {
      std::format_to(ctx.out(), "{}", c.compressed_fresh_ranges[i]);
      if (i + 1 != c.compressed_fresh_ranges.size())
        std::format_to(ctx.out(), "\n");
    }
    return ctx.out();
  }
};

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  Cafeteria cafeteria;
  std::cin >> cafeteria;

  std::println("cafeteria:\n{}", cafeteria);

  const lli ans = cafeteria.FreshIngredientsCount();
  std::println("Ans: {}", ans);

  return 0;
}
