#include <bits/stdc++.h>
#define DEBUG if (0)
#define lli long long int
#define ldouble long double

int N;
struct TestCase {
  std::vector<lli> a;

  std::vector<bool> visited;
  bool Can(const lli x) {
    std::fill(visited.begin(), visited.end(), false);
    std::queue<int> q;
    for (int i = 0; i < N; ++i) {
      if (a[i] > x) continue;
      q.emplace(i);
    }
    while (!q.empty()) {
      const int i = q.front();
      q.pop();
      if (visited[i]) continue;
      visited[i] = true;

      if (i && std::abs(a[i] - a[i - 1]) <= x) {
        q.emplace(i - 1);
      }
      if (i + 1 < N && std::abs(a[i] - a[i + 1]) <= x) {
        q.emplace(i + 1);
      }
    }

    for (int i = 0; i < N; ++i)
      if (!visited[i]) return false;
    return true;
  }

  bool Run() {
    if (!(std::cin >> N)) return false;
    a.resize(N);
    visited.resize(N);
    for (auto& ai : a) std::cin >> ai;

    lli lo = 0, hi = *std::max_element(a.begin(), a.end());
    while (lo < hi) {
      const lli mid = (lo + hi) >> 1;
      if (Can(mid))
        hi = mid;
      else
        lo = mid + 1;
    }
    std::cout << lo << "\n";

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
    std::cout << "Case #" << t << ": ";
    test_case.Run();
  }

  return 0;
}
