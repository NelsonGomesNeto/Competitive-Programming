#include <bits/stdc++.h>
#define DEBUG if (0)
#define lli long long int
#define ldouble long double

/*
Really nice "Parallel Binary Search" problem.

### Idea
For each, query we'll do a binary search for the answer in the following way.
To know if it would be possible with the first `k` edges, we connect those edges
and check if the sub graph with `x` and `y` has at least `z` vertices.

Since the check is identical for all queries, we can do the check once and
update the next guess for each query.

That way, we'll only do O(lg(m)) checks. So, the final complexity is
O(max(m, q)*lg(m)).
*/

struct DSU {
  int size;
  std::vector<int> parents;
  DSU() : size(0) { parents.clear(); }
  DSU(const int sz) : size(sz) { parents.resize(size, -1); }
  void Reset() { std::ranges::fill(parents, -1); }
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

struct TestCase {
  int n, m;
  std::vector<std::pair<int, int>> edges;
  int q;
  std::vector<std::tuple<int, int, int>> queries;

  std::vector<int> ans;
  struct BinarySearchParams {
    int lo, hi;
  };
  std::vector<std::vector<int>> searches_by_guess;
  std::vector<BinarySearchParams> searches;
  DSU dsu;
  void Checks() {
    for (const auto [i, edge] : edges | std::views::enumerate) {
      // i + 1 because it's after adding the i-th edge.
      const int guess = (int)i + 1;
      const auto [u, v] = edge;
      dsu.Merge(u, v);

      for (const int qi : searches_by_guess[guess]) {
        auto& [lo, hi] = searches[qi];
        const auto [x, y, z] = queries[qi];
        const int total_size =
            (dsu.SameSet(x, y) ? 0 : dsu.SetSize(x)) + dsu.SetSize(y);
        if (total_size >= z)
          hi = guess;
        else {
          lo = guess + 1;
          // This doesn't change the complexity but speeds stuff up a bit.
          if (lo != hi) {
            const int mid = (lo + hi) >> 1;
            searches_by_guess[mid].push_back(qi);
          }
        }
      }
    }
  }
  void ParallelBinarySearch() {
    searches.resize(q, {1, m});
    searches_by_guess.resize(m + 1, {});
    while (true) {
      bool all_finished = true;
      for (auto [u, params] : searches | std::views::enumerate) {
        const auto [lo, hi] = params;
        if (lo == hi) continue;
        const int mid = (lo + hi) >> 1;
        searches_by_guess[mid].push_back((int)u);
        all_finished = false;
      }
      if (all_finished) break;

      Checks();

      for (auto& mids : searches_by_guess) mids.clear();
      dsu.Reset();
    }
    for (auto [u, params] : searches | std::views::enumerate) {
      ans[u] = params.lo;
    }
  }

  bool Run() {
    if (!(std::cin >> n >> m)) return false;
    edges.resize(m);
    for (auto& [u, v] : edges) {
      std::cin >> u >> v;
      --u, --v;
    }

    std::cin >> q;
    queries.resize(q);
    for (auto& [x, y, z] : queries) {
      std::cin >> x >> y >> z;
      --x, --y;
    }

    dsu = DSU(n);
    ans.resize(q);
    ParallelBinarySearch();
    std::ostringstream sout;
    for (const int ansi : ans) std::println(sout, "{}", ansi);
    std::print("{}", sout.str());

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
