#include <bits/stdc++.h>

struct Dinner {
  std::map<std::string, int> id_by_name;
  std::vector<std::string> name_by_id;
  std::vector<std::tuple<int, int, int>> edges;
  std::vector<std::vector<int>> happiness_by_edge;
  int n;
  int AddVertex(const std::string& u) {
    const auto [it, inserted] = id_by_name.try_emplace(u, name_by_id.size());
    if (inserted) name_by_id.push_back(u);
    return it->second;
  }
  void BuildGraph() {
    n = name_by_id.size();
    // Add edges with `me`
    for (int i = 1; i < n; ++i) {
      edges.emplace_back(0, i, 0);
      edges.emplace_back(i, 0, 0);
    }
    happiness_by_edge.resize(n, std::vector<int>(n));
    for (const auto [uid, vid, delta] : edges) {
      happiness_by_edge[uid][vid] = delta;
    }
  }
  friend std::istream& operator>>(std::istream& sin, Dinner& d) {
    d.AddVertex("me");
    for (std::string line; std::getline(sin, line);) {
      assert(line.back() == '.');
      line.pop_back();
      std::istringstream lin(line);
      std::vector<std::string> words;
      for (std::string word; lin >> word;) words.push_back(word);

      const std::string u = words[0], v = words.back();
      const int uid = d.AddVertex(u), vid = d.AddVertex(v);
      const int delta = std::stoi(words[3]) * (words[2] == "lose" ? -1 : 1);
      d.edges.emplace_back(uid, vid, delta);
    }
    d.BuildGraph();
    return sin;
  }

  int FindBestOrder() const {
    std::println("FindBestOrder:");
    std::vector<int> p(n);
    std::ranges::iota(p, 0);
    int best_happiness = std::numeric_limits<int>::min();
    std::vector<int> best_permutation;
    do {
      int happiness =
          happiness_by_edge[p.back()][p[0]] + happiness_by_edge[p[0]][p.back()];
      for (const auto [u, v] : p | std::views::adjacent<2>) {
        happiness += happiness_by_edge[u][v] + happiness_by_edge[v][u];
      }
      if (happiness > best_happiness)
        best_happiness = happiness, best_permutation = p;
    } while (std::ranges::next_permutation(p).found);
    std::println("\tbest order: {}",
                 best_permutation | std::views::transform([&](const int u) {
                   return name_by_id[u];
                 }));
    return best_happiness;
  }
};
template <>
struct std::formatter<Dinner> {
  constexpr auto parse(std::format_parse_context& ctx) { return ctx.begin(); }
  template <class FormatContext>
  auto format(const Dinner& d, FormatContext& ctx) const {
    return std::format_to(
        ctx.out(), "{}",
        d.edges |
            std::views::transform([&](const std::tuple<int, int, int>& uvd) {
              const auto [uid, vid, delta] = uvd;
              return std::format("\t{} -[{}]> {}", d.name_by_id[uid], delta,
                                 d.name_by_id[vid]);
            }) |
            std::views::join_with('\n') | std::ranges::to<std::string>());
  }
};

int main() {
  Dinner dinner;
  std::cin >> dinner;

  std::println("dinner:\n{}", dinner);

  const int ans = dinner.FindBestOrder();
  std::println("ans: {}", ans);

  return 0;
}
