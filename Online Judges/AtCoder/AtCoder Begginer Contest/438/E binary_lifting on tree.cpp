#include <bits/stdc++.h>
#define DEBUG if (0)
#define lli long long int
#define ldouble long double

const int kMaxAncestor = 20;

struct TestCase {
  int n, q;
  std::vector<int> a;
  std::vector<std::vector<int>> rev_a;
  std::vector<int> roots;
  std::vector<std::vector<int>> tree;
  std::vector<std::pair<lli, int>> queries;

  struct Bucket {
    bool at_walk;
    int pos_at_cycle;
    int cycle_index;
  };
  std::vector<Bucket> buckets;

  std::vector<int> depth;
  std::vector<lli> sum_from_root;
  std::vector<std::vector<int>> ancestor;
  void Dfs(const int root, const int u, const int d = 0, lli sum = 0) {
    depth[u] = d;
    if (u != root) {
      buckets[u] = {.at_walk = true,
                    .pos_at_cycle = buckets[root].pos_at_cycle,
                    .cycle_index = buckets[root].cycle_index};
      sum += u + 1;
    }
    sum_from_root[u] = sum;
    for (const int v : tree[u]) {
      ancestor[0][v] = u;
      Dfs(root, v, d + 1, sum);
    }
  }
  void PrecalcTrees() {
    depth.resize(n), sum_from_root.resize(n);
    ancestor.resize(kMaxAncestor, std::vector<int>(n, -1));
    for (const int u : roots) {
      Dfs(u, u);
    }
    for (int d = 1; d < kMaxAncestor; ++d) {
      for (int u = 0; u < n; ++u) {
        const int half_ancestor = ancestor[d - 1][u];
        if (half_ancestor == -1) continue;
        ancestor[d][u] = ancestor[d - 1][half_ancestor];
      }
    }
  }

  bool Run() {
    if (!(std::cin >> n >> q)) return false;
    a.resize(n), rev_a.resize(n, {}), tree.resize(n, {});
    for (auto [i, ai] : a | std::views::enumerate) {
      std::cin >> ai;
      --ai;
      rev_a[ai].push_back((int)i);
    }
    queries.resize(q);
    for (auto& [ti, bi] : queries) {
      std::cin >> ti >> bi;
      --bi;
    }

    std::vector<int> done(n, -1);
    std::vector<std::vector<int>> cycles;
    std::vector<std::vector<lli>> cycles_acc;
    std::vector<std::vector<int>> walks;
    std::vector<std::vector<lli>> walks_acc;
    buckets.resize(n,
                   {.at_walk = false, .pos_at_cycle = -1, .cycle_index = -1});
    std::vector<lli> cycle_sum;
    for (int i = 0; i < n; ++i) {
      if (done[i] != -1) {
        continue;
      }

      // Find `u` belonging to a cycle
      done[i] = i;
      int u = a[i];
      while (done[u] == -1) {
        done[u] = i;
        u = a[u];
      }
      // Already processed
      if (done[u] != i) continue;

      std::vector<int> cycle;
      cycle.push_back(u);
      int v = a[u];
      while (v != u) {
        cycle.push_back(v);
        v = a[v];
      }
      std::vector<lli> cycle_acc(2 * cycle.size() + 1);
      for (auto [j, val] : cycle_acc | std::views::take(2 * cycle.size()) |
                               std::views::enumerate) {
        cycle_acc[j + 1] = cycle_acc[j] + (cycle[j % cycle.size()] + 1);
      }
      const int curr_cycle_index = (int)cycles.size();
      cycles.push_back(cycle);
      cycles_acc.push_back(cycle_acc);
      for (const auto [j, w] : cycle | std::views::enumerate) {
        buckets[w] = {
            .at_walk = false,
            .pos_at_cycle = (int)j,
            .cycle_index = curr_cycle_index,
        };
      }
      cycle_sum.push_back(
          std::reduce(cycle.begin(), cycle.end(), 0LL, std::plus()) +
          cycle.size());
    }

    // Each cycle will have trees around it
    // For each node in the tree, we can do binary lifting to find the k-th
    // ancestor and then compute the sum of the path
    for (int i = 0; i < n; ++i) {
      if (buckets[i].cycle_index != -1) continue;
      tree[i] = rev_a[i];
    }
    for (const auto [cycle_index, cycle] : cycles | std::views::enumerate) {
      for (const auto [pos_at_cycle, u] : cycle | std::views::enumerate) {
        for (const int v : rev_a[u]) {
          if (buckets[v].cycle_index != -1) continue;
          tree[u].push_back(v);
        }
        if (!tree[u].empty()) roots.push_back(u);
      }
    }
    PrecalcTrees();

    for (const auto [ti, bi] : queries) {
      const Bucket& b = buckets[bi];
      assert(b.cycle_index != -1);
      DEBUG std::println("ti {} bi {} | at_walk {} pos_at_cycle {} cycle {}",
                         ti, bi, b.at_walk, b.pos_at_cycle,
                         cycles[b.cycle_index]);
      const auto [sum_until_cycle, t_used] = [&]() -> std::pair<lli, lli> {
        if (!b.at_walk) return std::make_pair(0, 0);
        const int dist_to_cycle = depth[bi];
        if (ti <= dist_to_cycle) {
          int anc = bi;
          for (int p = 0; p < kMaxAncestor; ++p) {
            if (~ti & (1 << p)) continue;
            anc = ancestor[p][anc];
            assert(anc != -1);
          }
          return std::make_pair(sum_from_root[bi] - sum_from_root[anc], ti);
        } else {
          return std::make_pair(sum_from_root[bi], (lli)dist_to_cycle);
        }
      }();
      DEBUG std::println("\tsum_until_cycle {} t_used {}", sum_until_cycle,
                         t_used);
      const lli ans = [&]() {
        if (t_used == ti) return sum_until_cycle;
        const std::vector<int>& cycle = cycles[b.cycle_index];
        const lli t = ti - t_used;
        const lli loops = t / (int)cycle.size();
        const lli loops_sum = cycle_sum[b.cycle_index] * loops;
        const lli rem_t = t % (int)cycle.size();
        DEBUG std::println("\tt {} | loops {} loops_sum {} | rem_t {}", t,
                           loops, loops_sum, rem_t);
        if (rem_t == 0) return sum_until_cycle + loops_sum;
        const lli rem_walk = cycles_acc[b.cycle_index][b.pos_at_cycle + rem_t] -
                             cycles_acc[b.cycle_index][b.pos_at_cycle];
        DEBUG std::println("\trem_t {} | rem_walk {}", rem_t, rem_walk);
        return sum_until_cycle + loops_sum + rem_walk;
      }();
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
