#include <bits/stdc++.h>

const int kSafeSize = 100;

struct Rotation {
  char direction;
  int clicks;
  Rotation(std::istream&& sin) { sin >> direction >> clicks; }
  Rotation(const std::string& rotation)
      : Rotation(std::istringstream(rotation)) {}
};
template <>
struct std::formatter<Rotation> {
  constexpr auto parse(std::format_parse_context& ctx) {
    auto it = ctx.begin();
    return it;
  }
  template <class FormatContext>
  auto format(const Rotation& r, FormatContext& ctx) const {
    return std::format_to(ctx.out(), "{}{}", r.direction, r.clicks);
  }
};

struct Safe {
  std::vector<Rotation> rotations;

  friend std::istream& operator>>(std::istream& sin, Safe& s) {
    s.rotations.clear();
    for (std::string line; std::getline(sin, line) && !line.empty();) {
      s.rotations.emplace_back(line);
    }
    return sin;
  }

  int CountZeroes(const int prv, const Rotation& r) const {
    const int dist = [&]() {
      if (r.direction == 'L')
        return prv;
      else
        return (kSafeSize - prv) % kSafeSize;
    }();
    const int zero_clicks =
        r.clicks >= dist ? 1 + (r.clicks - dist) / kSafeSize : 0;
    // If counting, don't count twice if already at 0.
    const int already_at_zero = zero_clicks && prv == 0 ? 1 : 0;
    const int ans = zero_clicks - already_at_zero;
    std::println("\tprv {} | {} | zero_clicks {} | ans {}", prv, r, zero_clicks,
                 ans);
    return ans;
  }

  int Password() const {
    int prv = 50;
    int curr = 50;
    int ans = 0;
    for (const auto& r : rotations) {
      prv = curr;
      if (r.direction == 'L') {
        curr -= r.clicks;
      } else {
        curr += r.clicks;
      }
      curr = ((curr % kSafeSize) + kSafeSize) % kSafeSize;

      ans += CountZeroes(prv, r);
    }
    return ans;
  }
};

int main() {
  Safe safe;
  std::cin >> safe;
  std::println("rotations: {}", safe.rotations);

  const int ans = safe.Password();
  std::println("Password: {}", ans);

  return 0;
}