#include <bits/stdc++.h>

struct LocationGraph {
  std::vector<std::tuple<std::string, std::string, int>> raw_edges;
  std::map<std::string, int> vertex_id_by_name;
  std::vector<std::string> vertex_name_by_id;
  int n;
  std::vector<std::vector<std::pair<int, int>>> graph;
  std::vector<std::vector<int>> mat;
  void AddVertex(const std::string& u) {
    const auto [it, inserted] =
        vertex_id_by_name.try_emplace(u, vertex_id_by_name.size());
    if (inserted) vertex_name_by_id.push_back(u);
  }
  void Build() {
    for (const auto& [u, v, d] : raw_edges) {
      AddVertex(u);
      AddVertex(v);
    }
    assert(vertex_id_by_name.size() == vertex_name_by_id.size());
    n = vertex_id_by_name.size();
    graph.resize(n);
    mat.resize(n, std::vector<int>(n, -1));
    for (const auto& [u, v, d] : raw_edges) {
      const int uid = vertex_id_by_name[u];
      const int vid = vertex_id_by_name[v];
      graph[uid].emplace_back(vid, d);
      graph[vid].emplace_back(uid, d);
      mat[uid][vid] = mat[vid][uid] = d;
    }
  }

  int Evaluate(const std::vector<int>& permutation) const {
    int total_dist = 0;
    for (const auto [u, v] : permutation | std::views::adjacent<2>) {
      const int dist = mat[u][v];
      if (dist == -1) return std::numeric_limits<int>::min();
      total_dist += dist;
    }
    return total_dist;
  }
  int TravelingSalesman() const {
    std::println("TravelingSalesman:");
    const auto start = std::chrono::high_resolution_clock::now();
    std::vector<int> permutation(n);
    std::ranges::iota(permutation, 0);

    std::vector<int> best_permutation;
    int best_ans = std::numeric_limits<int>::min();
    do {
      const int v = Evaluate(permutation);
      // Longest path instead of shortest
      if (v > best_ans) best_ans = v, best_permutation = permutation;
    } while (std::ranges::next_permutation(permutation).found);
    const auto end = std::chrono::high_resolution_clock::now();
    const auto duration =
        std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    std::println("\t\texecution time: {}", duration);

    std::println("\t{} = {}",
                 best_permutation | std::views::transform([&](const int u) {
                   return std::format("{}", vertex_name_by_id[u]);
                 }) | std::views::join_with(std::string_view(" -> ")) |
                     std::ranges::to<std::string>(),
                 best_ans);

    return best_ans;
  }

  friend std::istream& operator>>(std::istream& sin, LocationGraph& g) {
    for (std::string line; std::getline(sin, line);) {
      std::istringstream lin(line);
      std::string u, v;
      int d;
      lin >> u;
      lin.ignore(3);  // size of `to `
      lin >> v;
      lin.ignore(3);  // size of `= `
      lin >> d;
      g.raw_edges.emplace_back(u, v, d);
    }
    g.Build();
    return sin;
  }
};
template <>
struct std::formatter<LocationGraph> {
  constexpr auto parse(std::format_parse_context& ctx) { return ctx.begin(); }
  template <class FormatContext>
  auto format(const LocationGraph& g, FormatContext& ctx) const {
    for (const auto& [uid, edges] : g.graph | std::views::enumerate) {
      for (const auto [vid, d] : edges) {
        if (uid > vid) continue;
        std::format_to(ctx.out(), "\t{}({}) <[{}]> {}({})\n",
                       g.vertex_name_by_id[uid], uid, d,
                       g.vertex_name_by_id[vid], vid);
      }
    }
    return ctx.out();
  }
};

int main() {
  LocationGraph location_graph;
  std::cin >> location_graph;

  std::println("graph:\n{}", location_graph);

  const int ans = location_graph.TravelingSalesman();
  std::println("ans: {}", ans);

  return 0;
}
