#include <bits/stdc++.h>
#define lli long long int

struct Pos {
  lli x, y, z;
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
    std::pair<int, int> last_pair;
    for (const auto& [d, i, j] : dists) {
      dsu.Merge(i, j);
      if (dsu.SetSize(0) == (int)jboxes.size()) {
        last_pair = {i, j};
        break;
      }
    }

    const auto& a = jboxes[last_pair.first];
    const auto& b = jboxes[last_pair.second];
    std::println("last_pair: {} | {}", a, b);
    const lli ans = a.x * b.x;
    return ans;
  }
};
template <>
struct std::formatter<Playground> {
  constexpr auto parse(std::format_parse_context& ctx) { return ctx.begin(); }
  template <class FormatContext>
  auto format(const Playground& p, FormatContext& ctx) const {
    // Finally, a oneliner to print a range with custom separators! \o/
    return std::format_to(ctx.out(), "{}",
                          p.jboxes | std::views::transform([](const Pos& pos) {
                            return std::format("\t{}", pos);
                          }) | std::views::join_with('\n') |
                              std::ranges::to<std::string>());
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
