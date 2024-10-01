#include <bits/stdc++.h>
#define DEBUG if (0)
#define lli long long int
#define ldouble long double

struct TestCase {
  int n, g;
  std::vector<int> stones;

  std::pair<int, int> Solve() {
    std::cin >> n >> g;
    stones.resize(n);
    for (int& s : stones) std::cin >> s;
    std::sort(stones.begin(), stones.end());

    int closest_dist = std::numeric_limits<int>::max(), closest = -1;
    for (int i = 0; i < stones.size(); ++i) {
      const int s = stones[i];

      int dist = std::abs(s - g);
      if (dist > closest_dist) continue;
      closest_dist = dist;
      closest = stones.size() - i;
    }

    return std::make_pair(closest, closest_dist);
  }
};
TestCase test_case;

int main() {
  int test_cases;
  std::cin >> test_cases;
  for (int t = 1; t <= test_cases; ++t) {
    test_case = TestCase{};
    const auto [stone, dist] = test_case.Solve();
    std::cout << "Case #" << t << ": " << stone << " " << dist << "\n";
  }
  return 0;
}