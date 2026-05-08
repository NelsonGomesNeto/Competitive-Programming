#include <bits/stdc++.h>
#define DEBUG if (0)
#define lli long long int
#define ldouble long double

/*
if semi-prime:
  count p1
  count p2
  count semi-prime
elif prime:
  count semi-prime with prime
  count prime - prime
else:
  0
*/

const int kMaxX = 2e5;
bool composite[kMaxX + 1];
std::vector<std::pair<int, int>> semi_primes(kMaxX + 1, std::make_pair(-1, -1));
std::vector<int> primes;
void InitPrimes() {
  composite[0] = composite[1] = true;
  for (int i = 2; i <= kMaxX; ++i) {
    if (!composite[i]) primes.push_back(i);
    for (int j = 0; i * primes[j] <= kMaxX; ++j) {
      composite[i * primes[j]] = true;
      if (i % primes[j] == 0) break;
    }
  }

  for (int i = 0; i < primes.size(); ++i) {
    const int p1 = primes[i];
    for (int j = i; j < primes.size() && (lli)p1 * primes[j] <= kMaxX; ++j) {
      semi_primes[p1 * primes[j]] = std::make_pair(p1, primes[j]);
    }
  }
}

struct TestCase {
  int n;
  std::vector<int> a;
  bool Run() {
    if (!(std::cin >> n)) return false;
    a.resize(n);
    for (auto& ai : a) std::cin >> ai;

    lli ans = 0;
    int total_primes = 0;
    std::vector<int> cnt_primes(n + 1, 0), cnt_semi_primes(n + 1, 0);
    std::vector<int> cnt_primes_in_semi_primes(n + 1, 0);
    for (const auto& ai : a) {
      /*
      if semi-prime:
        count p1
        count p2
        count semi-prime
      elif prime:
        count semi-prime with prime
        count prime - prime
      else:
        0
      */
      if (semi_primes[ai].first != -1) {
        ++cnt_semi_primes[ai];
        ++cnt_primes_in_semi_primes[semi_primes[ai].first];
        if (semi_primes[ai].first != semi_primes[ai].second)
          ++cnt_primes_in_semi_primes[semi_primes[ai].second];

        ans += cnt_primes[semi_primes[ai].first];
        if (semi_primes[ai].first != semi_primes[ai].second)
          ans += cnt_primes[semi_primes[ai].second];
        ans += cnt_semi_primes[ai];

      } else if (!composite[ai]) {
        ++cnt_primes[ai];
        ++total_primes;

        ans += total_primes - cnt_primes[ai];
        ans += cnt_primes_in_semi_primes[ai];
      }
    }
    std::cout << ans << "\n";

    return true;
  }
};
TestCase test_case;

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  InitPrimes();

  int test_cases;
  std::cin >> test_cases;
  for (int t = 1; t <= test_cases; ++t) {
    test_case = TestCase{};
    test_case.Run();
  }

  return 0;
}
