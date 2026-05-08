#include <bits/stdc++.h>
#define DEBUG if (0)
#define lli long long int
#define ldouble long double

struct TestCase {
  int n, q;
  std::vector<int> values;

  std::vector<int> a;
  struct Query {
    int x, r, i;
    bool operator<(const Query& other) const { return x > other.x; }
  };
  std::vector<Query> queries;
  bool Run() {
    if (!(std::cin >> n >> q)) return false;
    a.resize(n);
    for (auto& ai : a) std::cin >> ai;
    values = a;

    queries.resize(q);
    for (int i = 0; i < q; ++i) queries[i].i = i;
    for (auto& [x, r, i] : queries) {
      std::cin >> r >> x;
      --r;
      values.push_back(x);
    }
    std::sort(queries.begin(), queries.end());

    std::sort(values.begin(), values.end());
    values.resize(std::distance(values.begin(),
                                std::unique(values.begin(), values.end())));

    int done_i = 0;
    for (const auto& [x, r, i] : queries) {
      while (done_i < n && a[done_i] <= x) {
        // Update
        ++done_i;
      }
    }

    return true;
  }
};
TestCase test_case;

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  // int test_cases;
  // std::cin >> test_cases;
  // for (int t = 1; t <= test_cases; ++t) {
  //   test_case = TestCase{};
  //   test_case.Run();
  // }

  do {
    test_case = TestCase{};
  } while (test_case.Run());

  return 0;
}
