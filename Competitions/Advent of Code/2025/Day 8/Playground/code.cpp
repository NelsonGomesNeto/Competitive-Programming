#include <bits/stdc++.h>
#define lli long long int
#define ldouble long double

struct Pos {
  lli x, y, z;
  Pos() {}
  Pos(std::istream&& sin)
      : x([&]() {
          lli a;
          sin >> a;
          sin.ignore(std::numeric_limits<std::streamsize>::max(), ',');
          return a;
        }()),
        y([&]() {
          lli a;
          sin >> a;
          sin.ignore(std::numeric_limits<std::streamsize>::max(), ',');
          return a;
        }()),
        z([&]() {
          lli a;
          sin >> a;
          return a;
        }()) {}
  Pos(const std::string& pos_str) : Pos(std::istringstream(pos_str)) {}

  double Dist(const auto& o) const {
    return std::sqrt((x - o.x) * (x - o.x) + (y - o.y) * (y - o.y) +
                     (z - o.z) * (z - o.z));
  }
};
template <>
struct std::formatter<Pos> {
  constexpr auto parse(std::format_parse_context& ctx) { return ctx.begin(); }
  template <class FormatContext>
  auto format(const Pos& p, FormatContext& ctx) const {
    return std::format_to(ctx.out(), "({}, {}, {})", p.x, p.y, p.z);
  }
};

struct DSU {
  int size;
  std::vector<int> parents;
  DSU() : size(0) { parents.clear(); }
  DSU(const int sz) : size(sz) { Init(); }
  void Init() { parents.resize(size, -1); }
  int Root(const int u) {
    return parents[u] < 0 ? u : parents[u] = Root(parents[u]);
  }
  void Merge(int u, int v) {
    u = Root(u), v = Root(v);
    if (u == v) return;
    if (parents[u] > parents[v]) std::swap(u, v);
    parents[u] += parents[v];
    parents[v] = u;
  }
  int SetSize(const int u) { return -parents[Root(u)]; }
  bool SameSet(const int u, const int v) { return Root(u) == Root(v); }
};

struct Playground {
  std::vector<Pos> jboxes;
  DSU dsu;

  friend std::istream& operator>>(std::istream& sin, Playground& p) {
    p.jboxes.clear();
    for (std::string line; std::getline(sin, line) && !line.empty();) {
      p.jboxes.emplace_back(line);
    }
    p.dsu = DSU(p.jboxes.size());
    return sin;
  }

  lli Connect() {
    std::vector<std::tuple<double, int, int>> dists;
    dists.reserve(jboxes.size() * jboxes.size());
    for (const auto& [i, a] : std::views::enumerate(jboxes)) {
      for (const auto& [j, b] :
           std::views::enumerate(jboxes) | std::views::drop(i + 1)) {
        dists.emplace_back(a.Dist(b), i, j);
      }
    }
    std::ranges::sort(dists);

    const int to_connect = (int)jboxes.size();
    for (const auto& [d, i, j] : dists | std::views::take(to_connect)) {
      dsu.Merge(i, j);
    }

    std::vector<std::pair<int, int>> sets;
    sets.reserve(jboxes.size());
    for (int i = 0; i < (int)jboxes.size(); ++i) {
      if (dsu.Root(i) != i) continue;
      sets.emplace_back(dsu.SetSize(i), i);
    }
    std::ranges::sort(sets, std::greater());

    lli ans = 1;
    const int to_multiply = 3;
    for (const auto& [size, i] : sets | std::views::take(to_multiply)) {
      std::println("\t{}, sz: {}", i, size);
      ans *= size;
    }
    return ans;
  }
};
template <>
struct std::formatter<Playground> {
  constexpr auto parse(std::format_parse_context& ctx) { return ctx.begin(); }
  template <class FormatContext>
  auto format(const Playground& p, FormatContext& ctx) const {
    return std::format_to(ctx.out(), "{}", p.jboxes);
    // const auto joined_view =
    //     std::ranges::join_with_view(p.jboxes, std::string_view("\n"));
    // return std::format_to(ctx.out(), "{}",
    //                       std::string(joined_view.begin(),
    //                       joined_view.end()));
  }
};

int main() {
  Playground playground;
  std::cin >> playground;

  std::println("playground:\n{}", playground);

  const lli ans = playground.Connect();
  std::println("Ans: {}", ans);

  return 0;
}
