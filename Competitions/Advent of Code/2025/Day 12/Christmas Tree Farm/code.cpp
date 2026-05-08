#include <bits/stdc++.h>

std::array<std::tuple<char, char, char>, 256> kColorMap;

void Rotate(std::vector<std::string>& grid) {
  assert(grid.size() == grid[0].size());
  const int n = grid.size();
  std::vector<std::string> copy = grid;
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      grid[j][n - i - 1] = copy[i][j];
    }
  }
}
void FlipX(std::vector<std::string>& grid) {
  assert(grid.size() == grid[0].size());
  const int n = grid.size();
  std::vector<std::string> copy = grid;
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      grid[i][n - j - 1] = copy[i][j];
    }
  }
}

void FlipY(std::vector<std::string>& grid) {
  assert(grid.size() == grid[0].size());
  const int n = grid.size();
  std::vector<std::string> copy = grid;
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      grid[n - i - 1][j] = copy[i][j];
    }
  }
}

struct Present {
  int n, m;
  std::vector<std::string> grid;
  char name;
  std::vector<std::vector<std::string>> rotations;
  int filled_area;
  friend std::istream& operator>>(std::istream& sin, Present& p) {
    for (std::string line;
         std::getline(sin, line) && !line.empty() && line[0] != '\n';) {
      p.grid.push_back(line);
    }
    p.n = (int)p.grid.size(), p.m = (int)p.grid[0].size();
    p.BuildRotations();
    p.filled_area = 0;
    for (int i = 0; i < p.n; ++i) {
      for (int j = 0; j < p.m; ++j) {
        if (p.grid[i][j] == '.') continue;
        ++p.filled_area;
      }
    }
    return sin;
  }
  void BuildRotations() {
    std::vector<std::string> curr = grid;
    for (int i = 0; i < 4; ++i) {
      rotations.push_back(curr);
      Rotate(curr);
    }

    FlipX(curr);
    for (int i = 0; i < 4; ++i) {
      rotations.push_back(curr);
      Rotate(curr);
    }
    FlipX(curr);

    FlipY(curr);
    for (int i = 0; i < 4; ++i) {
      rotations.push_back(curr);
      Rotate(curr);
    }
    FlipY(curr);

    FlipX(curr);
    FlipY(curr);
    for (int i = 0; i < 4; ++i) {
      rotations.push_back(curr);
      Rotate(curr);
    }
    FlipX(curr);
    FlipY(curr);

    std::ranges::sort(rotations);
    rotations.resize(std::distance(
        rotations.begin(), std::unique(rotations.begin(), rotations.end())));
  }
};
template <>
struct std::formatter<Present> {
  constexpr auto parse(std::format_parse_context& ctx) { return ctx.begin(); }
  template <class FormatContext>
  auto format(const Present& p, FormatContext& ctx) const {
    return std::format_to(
        ctx.out(), "{}",
        p.grid | std::views::transform([](const std::string& line) {
          return std::format("{}", line);
        }) | std::views::join_with('\n') |
            std::ranges::to<std::string>());
  }
};

struct Region {
  int n, m;
  std::vector<int> requirements;
  int free_space;
  std::vector<std::string> grid;
  Region(std::istream&& sin) {
    sin >> n;
    sin.ignore(std::numeric_limits<std::streamsize>::max(), 'x');
    sin >> m;
    sin.ignore(std::numeric_limits<std::streamsize>::max(), ' ');
    for (int r; sin >> r;) {
      requirements.push_back(r);
    }
    grid.resize(n, std::string(m, '.'));
    free_space = n * m;
  }
  Region(const std::string& region_str)
      : Region(std::istringstream(region_str)) {}

  bool Fit(const int si, const int sj, const Present& p,
           const int rotation) const {
    assert(si + p.n - 1 < n);
    assert(sj + p.m - 1 < m);
    for (int i = si, endi = si + p.n; i < endi; ++i) {
      for (int j = sj, endj = sj + p.m; j < endj; ++j) {
        if (p.rotations[rotation][i - si][j - sj] == '.') continue;
        if (grid[i][j] != '.') return false;
      }
    }
    return true;
  }

  void Add(const int si, const int sj, const Present& p, const int rotation) {
    assert(si + p.n - 1 < n);
    assert(sj + p.m - 1 < m);
    for (int i = si, endi = si + p.n; i < endi; ++i) {
      for (int j = sj, endj = sj + p.m; j < endj; ++j) {
        if (p.rotations[rotation][i - si][j - sj] == '.') continue;
        grid[i][j] = p.name;
        --free_space;
      }
    }
  }
  void Remove(const int si, const int sj, const Present& p,
              const int rotation) {
    assert(si + p.n - 1 < n);
    assert(sj + p.m - 1 < m);
    for (int i = si, endi = si + p.n; i < endi; ++i) {
      for (int j = sj, endj = sj + p.m; j < endj; ++j) {
        if (p.rotations[rotation][i - si][j - sj] == '.') continue;
        grid[i][j] = '.';
        ++free_space;
      }
    }
  }
};
template <>
struct std::formatter<Region> {
  constexpr auto parse(std::format_parse_context& ctx) { return ctx.begin(); }
  template <class FormatContext>
  auto format(const Region& r, FormatContext& ctx) const {
    return std::format_to(ctx.out(), "{}x{}: {}", r.n, r.m, r.requirements);
  }
};

struct Farm {
  std::vector<Present> presents;
  std::vector<Region> regions;
  friend std::istream& operator>>(std::istream& sin, Farm& f) {
    for (std::string line; std::getline(sin, line) && !line.empty();) {
      if (line[1] == ':') {
        Present present;
        sin >> present;
        present.name = '0' + (int)f.presents.size();
        f.presents.push_back(present);
      } else {
        f.regions.emplace_back(line);
      }
    }
    return sin;
  }

  bool IsPossible(Region& r, int ri = 0, int rj = 0) {
    if (ri == (int)r.requirements.size()) {
      return true;
    }
    if (rj == r.requirements[ri]) return IsPossible(r, ri + 1, 0);

    const Present& p = presents[ri];
    for (int i = 0, endi = r.n - p.n + 1; i < endi; ++i) {
      for (int j = 0, endj = r.m - p.m + 1; j < endj; ++j) {
        for (int rotation = 0; rotation < (int)p.rotations.size();
        ++rotation) {
          if (!r.Fit(i, j, p, rotation)) continue;
          r.Add(i, j, p, rotation);
          if (IsPossible(r, ri, rj + 1)) return true;
          r.Remove(i, j, p, rotation);
        }
      }
    }

    // This strategy is better for tighther spaces, but all tests cases have a
    // HUGE margin so we can trying blindingly is okay.
    // std::vector<std::tuple<int, int, int, int>> moves;
    // const Present& p = presents[ri];
    // for (int i = 0, endi = r.n - p.n + 1; i < endi; ++i) {
    //   for (int j = 0, endj = r.m - p.m + 1; j < endj; ++j) {
    //     for (int rotation = 0; rotation < (int)p.rotations.size(); ++rotation) {
    //       if (!r.Fit(i, j, p, rotation)) continue;
    //       r.Add(i, j, p, rotation);
    //       moves.emplace_back(r.free_space, i, j, rotation);
    //       r.Remove(i, j, p, rotation);
    //     }
    //   }
    // }
    // std::ranges::sort(moves, std::greater());
    // for (const auto& [_, i, j, rotation] : moves) {
    //   r.Add(i, j, p, rotation);
    //   if (IsPossible(r, ri, rj + 1)) return true;
    //   r.Remove(i, j, p, rotation);
    // }
    return false;
  }

  bool CheapIsPossible(const Region& r) {
    int area_sum = 0;
    for (const auto& [i, cnt] : r.requirements | std::views::enumerate) {
      area_sum += presents[i].filled_area * cnt;
    }
    return r.free_space >= area_sum;
  }

  int CountFillableRegions() {
    std::println("CountFillableRegions:\n");
    int ans = 0;
    for (auto [i, r] : regions | std::views::enumerate) {
      std::println("filling_region: {}", r);
      const bool is_possible = CheapIsPossible(r) && IsPossible(r);
      std::println("\tis_possible: {}", is_possible);
      if (is_possible) {
        std::println(
            "{}", r.grid | std::views::transform([](const std::string& line) {
                    return std::format("{}", line);
                  }) | std::views::join_with('\n') |
                      std::ranges::to<std::string>());
        std::ofstream image(std::format("images/{}.ppm", i),
                            std::ofstream::binary);
        std::println(image, "P6\n{} {}\n255\n", r.m, r.n);
        for (const auto& line : r.grid) {
          for (const auto c : line) {
            const auto [r, g, b] = kColorMap[c];
            std::print(image, "{}{}{}", r, g, b);
          }
        }
      }
      ans += is_possible;
    }
    return ans;
  }
};
template <>
struct std::formatter<Farm> {
  constexpr auto parse(std::format_parse_context& ctx) { return ctx.begin(); }
  template <class FormatContext>
  auto format(const Farm& f, FormatContext& ctx) const {
    return std::format_to(
        ctx.out(), "presents:\n{}\nregions:\n{}",
        f.presents | std::views::enumerate |
            std::views::transform([](const std::tuple<size_t, Present>& ip) {
              return std::format("{}:\n{}\n", std::get<0>(ip), std::get<1>(ip));
            }) |
            std::views::join_with('\n') | std::ranges::to<std::string>(),
        f.regions | std::views::transform([](const Region& r) {
          return std::format("{}", r);
        }) | std::views::join_with('\n') |
            std::ranges::to<std::string>());
  }
};

int main() {
  kColorMap['.'] = {0, 0, 0};
  kColorMap['0'] = {255, 0, 0};
  kColorMap['1'] = {0, 255, 0};
  kColorMap['2'] = {0, 0, 255};
  kColorMap['3'] = {255, 0, 255};
  kColorMap['4'] = {255, 255, 0};
  kColorMap['5'] = {255, 255, 255};

  Farm farm;
  std::cin >> farm;

  std::println("farm:\n{}", farm);
  std::println("\n-----------------\n");

  const int ans = farm.CountFillableRegions();
  std::println("Ans: {}", ans);

  return 0;
}
