#include <bits/stdc++.h>
#define DEBUG if (0)
#define lli long long int
#define ldouble long double

const int kNil = std::numeric_limits<int>::min();
const int kInf = 1e6;

struct TestCase {
  int n, fun_time, maximum_time;
  struct City {
    int start_time, f, dist;
    int WaitTime(const int time) const {
      if (time < start_time) return start_time - time;
      // time = s + f*x
      // x = ceil((time - s) / f)
      const int x = (time - start_time) / f + ((time - start_time) % f != 0);
      const int next_bus = start_time + f * x;
      return next_bus - time;
    }
  };
  std::vector<City> cities;

  std::vector<std::vector<int>> memo;
  int Solve(int i = 0, int time = 0) {
    if (i == n - 1) return 0;
    int& ans = memo[i][time];
    if (ans != kNil) return ans;

    ans = -kInf;
    const auto& city = cities[i];
    auto Try = [&](const int new_time, const int to_add) {
      const int next_time = new_time + city.WaitTime(new_time) + city.dist;
      if (next_time > maximum_time) return;
      ans = std::max(ans, Solve(i + 1, next_time) + to_add);
    };
    Try(time, 0);
    Try(time + fun_time, 1);

    return ans;
  }

  bool Run(const int test_case) {
    if (!(std::cin >> n >> fun_time >> maximum_time)) return false;
    cities.resize(n - 1);
    for (auto& [s, f, d] : cities) std::cin >> s >> f >> d;

    memo.resize(n, std::vector<int>(maximum_time + 1, kNil));
    const int ans = Solve();
    std::cout << "Case #" << test_case << ": ";
    if (ans < 0)
      std::cout << "IMPOSSIBLE\n";
    else
      std::cout << ans << "\n";

    return true;
  }
};
TestCase test_case;

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int test_cases;
  std::cin >> test_cases;
  for (int t = 1; t <= test_cases; ++t) {
    test_case = TestCase{};
    test_case.Run(t);
  }

  return 0;
}
