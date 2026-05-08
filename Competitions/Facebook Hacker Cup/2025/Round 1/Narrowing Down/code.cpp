#include <bits/stdc++.h>
#define DEBUG if (1)
#define DEBUG2 if (0)
#define lli long long int
#define ldouble long double

/*
How many subarrays has xorsum 0?

Or rather, how many do not?

Answer will always be either N (if can't) or N - 1 (if can)

Try to think if there was just one bit!


*/

int N;
std::vector<lli> a;
struct TestCase {
  std::vector<lli> a;
  std::vector<lli> acc, sacc;

  lli Lol(const lli sz) {
    return sz > 0 ? 1 : 0;
    return (sz + 2) * (sz + 1) / 2LL * sz / 3LL;
  }

  bool Run() {
    if (!(std::cin >> N)) return false;
    a.resize(N);
    for (auto& ai : a) std::cin >> ai;

    sacc.resize(N);
    sacc[N - 1] = 0;
    for (int i = N - 1, z = 0; i >= 0; --i) {
      if (a[i] == 0) ++z;
      sacc[i] = z;
      if (a[i] != 0) z = 0;
    }

    std::map<lli, std::pair<lli, int>> cnt;
    acc.resize(N + 1);
    acc[0] = 0;
    for (int i = 0; i < N; ++i) {
      acc[i + 1] = acc[i] ^ a[i];
      auto [it, _] = cnt.emplace(acc[i + 1], std::make_pair(0LL, 0));
      // ++it->second.first;
      if (a[i] != 0) {
        it->second.first += Lol(1 + sacc[i]);
      }
    }

    DEBUG std::cout << "\n";

    DEBUG {
      std::cout << "acc:";
      for (const auto acci : acc) std::cout << " " << acci;
      std::cout << "\n";
      std::cout << "cnt:\n";
      for (const auto& [k, v] : cnt) {
        std::cout << "\t" << k << " " << v.first << " " << v.second << "\n";
      }
    }

    lli ans = (lli)(N + 2) * (lli)(N + 1) / 2LL * (lli)N / 3LL;

    for (int i = 0; i < N; ++i) {
      if (a[i] != 0) continue;
      int j = i;
      while (j + 1 < N && a[j + 1] == 0) ++j;
      const lli sz = j - i + 1;
      ans -= (sz + 2) * (sz + 1) / 2LL * sz / 3LL;
      break;
    }

    // Count all in acc which match `curr`
    lli curr = 0;
    auto Remove = [&]() {
      auto it = cnt.find(curr);
      if (it == cnt.end()) return;
      // --(it->second.first);
    };
    for (int i = 0; i < N; ++i) {
      int zleft = 0;
      if (a[i] == 0) {
        int j = i;
        while (j + 1 < N && a[j + 1] == 0) {
          ++j;
          Remove();
        }
        Remove();
        zleft = j - i + 1;
        i = j + 1;
      }
      if (i == N) break;

      curr ^= a[i];
      const lli to_find = curr ^ a[i];
      auto it = cnt.find(to_find);
      if (it == cnt.end()) {
        Remove();
        continue;
      }
      const lli count = it->second.first;
      const lli zeroes = it->second.second;
      DEBUG {
        int target = 0;
        for (int j = i; j < N; ++j) {
          lli sum = 0;
          for (int k = i; k <= j; ++k) sum ^= a[k];
          target += sum == 0;
        }
        std::cout << "\t" << i << " " << a[i] << " | s: " << to_find << " | "
                  << count << " " << target << " | " << zleft << " " << zeroes
                  << "\n";
      }
      ans -= count;
      // ans -= count;

      Remove();
    }

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
    std::cout << "Case #" << t << ": ";
    test_case.Run();
  }

  return 0;
}
