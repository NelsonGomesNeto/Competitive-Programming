#include <bits/stdc++.h>
#define DEBUG if (0)
#define lli long long int
#define ldouble long double

struct TestCase {
  int n, k;
  std::vector<int> a, b;
  std::vector<std::pair<int, int>> ab;
  std::vector<lli> ab_sum_min_k;

  lli Solve() {
    lli ans = std::numeric_limits<lli>::max();
    for (int i = n - 1; i >= k - 1; --i) {
      lli max_a = ab[i].first;
      lli sum_b = ab_sum_min_k[i];
      DEBUG {
        lli naive_sum_b = ab[i].second;
        std::priority_queue<int> bs;
        for (int j = 0; j < i; ++j) {
          bs.push(ab[j].second);
          while ((int)bs.size() >= k) bs.pop();
        }
        assert((int)bs.size() == k - 1);
        while (!bs.empty()) {
          sum_b += bs.top();
          bs.pop();
        }
        DEBUG std::cout << "\t" << i << " " << max_a << " " << naive_sum_b
                        << " " << ab_sum_min_k[i] << "\n";
      }
      lli curr = max_a * sum_b;
      ans = std::min(ans, curr);
    }
    return ans;
  }
  void Run() {
    std::cin >> n >> k;
    a.resize(n), b.resize(n);
    for (int& ai : a) std::cin >> ai;
    for (int& bi : b) std::cin >> bi;
    ab.resize(n);
    for (int i = 0; i < n; ++i) {
      ab[i] = std::make_pair(a[i], b[i]);
    }
    std::sort(ab.begin(), ab.end());

    ab_sum_min_k.resize(n + 1, 0);
    std::priority_queue<int> bs;
    lli curr_sum = 0;
    auto Add = [&](const int x) {
      curr_sum += x;
      bs.push(x);
      while ((int)bs.size() >= k) {
        curr_sum -= bs.top();
        bs.pop();
      }
    };
    for (int i = 0; i < n; ++i) {
      ab_sum_min_k[i] = ab[i].second + curr_sum;
      Add(ab[i].second);
    }
    DEBUG for (int i = 0; i <= n; ++i) {
      std::cout << "\t\t" << i << " " << ab_sum_min_k[i] << "\n";
    }

    lli ans = Solve();
    std::cout << ans << "\n";
  }
};
TestCase test_case;

int main() {
  int test_cases;
  std::cin >> test_cases;
  for (int t = 1; t <= test_cases; ++t) {
    test_case = TestCase{};
    test_case.Run();
  }
  return 0;
}
