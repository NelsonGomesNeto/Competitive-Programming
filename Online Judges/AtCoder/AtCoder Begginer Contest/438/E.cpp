#include <bits/stdc++.h>
#define DEBUG if (0)
#define lli long long int
#define ldouble long double

const int kMaxAncestor = 30;

struct TestCase {
  int n, q;
  std::vector<int> a;
  std::vector<std::pair<lli, int>> queries;

  std::vector<std::vector<std::pair<int, lli>>> ancestor;

  bool Run() {
    if (!(std::cin >> n >> q)) return false;
    a.resize(n);
    for (auto [i, ai] : a | std::views::enumerate) {
      std::cin >> ai;
      --ai;
    }
    queries.resize(q);
    for (auto& [ti, bi] : queries) {
      std::cin >> ti >> bi;
      --bi;
    }

    ancestor.resize(kMaxAncestor,
                    std::vector<std::pair<int, lli>>(n, {-1, -1}));
    for (int i = 0; i < n; ++i) {
      ancestor[0][i] = std::make_pair(a[i], (i + 1));
    }
    for (int d = 1; d < kMaxAncestor; ++d) {
      for (int i = 0; i < n; ++i) {
        const auto [anc, anc_sum] = ancestor[d - 1][i];
        ancestor[d][i] = std::make_pair(ancestor[d - 1][anc].first,
                                        ancestor[d - 1][anc].second + anc_sum);
      }
    }

    for (const auto [ti, bi] : queries) {
      const lli ans = [&]() {
        int u = bi;
        lli sum = 0;
        for (int p = 0; p < kMaxAncestor; ++p) {
          if (~ti & (1LL << p)) continue;
          const auto [anc, anc_sum] = ancestor[p][u];
          sum += anc_sum, u = anc;
        }
        return sum;
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
