#include <bits/stdc++.h>
#define DEBUG if (0)
#define lli long long int
#define ldouble long double

// x valid if p1 - p2 = x, p <= n
// x + p1 = p2

const int maxX = 1e7;
bool composite[maxX + 1];
std::vector<int> primes;

struct TestCase {
  int n;

  int Solve() {
    std::cin >> n;

    std::unordered_set<int> ans;
    for (int i = 0; i < primes.size(); ++i) {
      for (int j = i + 1; j < primes.size(); ++j) {
        const int sum = primes[i] + primes[j];
        if (sum > n) break;

        if (composite[sum]) continue;
        DEBUG std::cout << primes[i] << " " << primes[j] << "\n";
        ans.insert(primes[i]), ans.insert(primes[j]);
      }
      break;
    }

    return ans.size();
  }
};
TestCase test_case;

int main() {
  composite[0] = composite[1] = true;
  for (int i = 2; i <= maxX; ++i)
  {
    if (!composite[i]) primes.push_back(i);
    for (int j = 0; i*primes[j] <= maxX; ++j)
    {
      composite[i*primes[j]] = true;
      if (i % primes[j] == 0) break;
    }
  }

  int test_cases;
  std::cin >> test_cases;
  for (int t = 1; t <= test_cases; ++t) {
    test_case = TestCase{};
    const auto ans = test_case.Solve();
    std::cout << "Case #" << t << ": " << ans << "\n";
  }
  return 0;
}