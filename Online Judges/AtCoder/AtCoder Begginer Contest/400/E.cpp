#include <bits/stdc++.h>
#define DEBUG if (0)
#define lli long long int
#define ldouble long double

const lli kMaxA = 1e12;

const int kMaxX = 1e6;
bool composite[kMaxX + 1];
std::vector<int> primes;
std::vector<std::pair<lli, int>> pot_tables;
std::vector<lli> valid_numbers;

struct TestCase {
  int q;
  lli Solve(const lli x) {
    int lo = 0, hi = (int)valid_numbers.size() - 1;
    while (lo < hi) {
      int mid = (lo + hi + 1) >> 1;
      if (valid_numbers[mid] <= x)
        lo = mid;
      else
        hi = mid - 1;
    }
    return valid_numbers[lo];
  }
  bool Run() {
    if (!(std::cin >> q)) return false;
    for (int qi = 0; qi < q; ++qi) {
      lli a;
      std::cin >> a;
      lli ans = Solve(a);
      std::cout << ans << "\n";
    }
    return true;
  }
};
TestCase test_case;

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  composite[0] = composite[1] = true;
  for (int i = 2; i <= kMaxX; ++i) {
    if (!composite[i]) primes.push_back(i);
    for (int j = 0; i * primes[j] <= kMaxX; ++j) {
      composite[i * primes[j]] = true;
      if (i % primes[j] == 0) break;
    }
  }
  for (const lli op : primes) {
    lli p = op * op;
    while (p <= kMaxA) {
      pot_tables.emplace_back(p, op);
      p *= op;
      if (p > kMaxA) break;
      p *= op;
    }
  }
  std::sort(pot_tables.begin(), pot_tables.end());

  for (int i = 0; i < (int)pot_tables.size(); ++i) {
    const auto [ap, aop] = pot_tables[i];
    if (ap > kMaxA) break;
    const lli maxdivap = kMaxA / ap;
    for (int j = i + 1; j < (int)pot_tables.size(); ++j) {
      const auto [bp, bop] = pot_tables[j];
      if (aop == bop) continue;
      if (bp > kMaxA) break;
      if (bp > maxdivap) break;
      const lli curr = ap * bp;
      valid_numbers.push_back(curr);
    }
  }
  std::sort(valid_numbers.begin(), valid_numbers.end());
  valid_numbers.resize(
      std::distance(valid_numbers.begin(),
                    std::unique(valid_numbers.begin(), valid_numbers.end())));

  do {
    test_case = TestCase{};
  } while (test_case.Run());

  return 0;
}
