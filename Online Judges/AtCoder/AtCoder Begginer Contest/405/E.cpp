#include <bits/stdc++.h>
#define DEBUG if (0)
#define lli long long int
#define ldouble long double

const lli kMod = 998244353LL;
lli ModPow(lli x, lli y) {
  lli ans = 1;
  while (y) {
    if (y & 1LL) ans = ans * x % kMod;
    x = x * x % kMod, y >>= 1LL;
  }
  return ans;
}
lli Inv(lli x) { return ModPow(x, kMod - 2); }

namespace combinatorics {
const int kMaxX = 2e6 + 1;
lli fat[kMaxX], invFat[kMaxX];
lli Choose(lli n, lli k) {
  if (n < k) return 0;
  if (n < kMod) return fat[n] * invFat[k] % kMod * invFat[n - k] % kMod;
  lli ans = 1;
  while (n || k) {
    lli nn = n % kMod, kk = k % kMod;
    n /= kMod, k /= kMod;
    ans = ans * Choose(nn, kk) % kMod;
  }
  return ans;
}
// n = stars, k = bars
lli StarsAndBars(lli n, lli k) { return Choose(n + k, k); }
void Init() {
  fat[0] = 1;
  for (lli i = 1; i < kMaxX; i++) fat[i] = i * fat[i - 1] % kMod;
  for (int i = 0; i < kMaxX; i++) invFat[i] = Inv(fat[i]);
}
}  // namespace combinatorics

const lli kMaxV = 1e6;

struct TestCase {
  int a, b, c, d;

  std::vector<lli> memo;
  std::vector<std::vector<lli>> pref;
  lli Pref(const int i, const int j, const int k, const int l) {
    if (j == -1 || k == -1 || l == -1) return 0;

    int state = i + j + k;
    if (i == 0) state = j + k + l;
    else if (j == 0) state = k + l;
    else state = l;
    lli& ans = pref[state][i != 0 ? 0 : j != 0 ? 1 : 2];
    if (ans != -1) return ans;

    const lli res = [&]() {
      if (i)
        return combinatorics::StarsAndBars(i - 1, j) * Solve(0, b - j, k, l) %
               kMod;
      else if (j)
        return combinatorics::StarsAndBars(j - 1, k) * Solve(0, 0, c - k, l) %
               kMod;
      else if (k)
        return combinatorics::StarsAndBars(k - 1, l) * Solve(0, 0, 0, d - l) %
               kMod;
      else
        assert(false);
    }();
    const lli res2 = [&]() {
      if (i)
        return Pref(i, j - 1, k, l);
      else if (j)
        return Pref(i, j, k - 1, l);
      else if (k)
        return Pref(i, j, k, l - 1);
      else
        assert(false);
    }();
    return ans = (res + res2) % kMod;
  }
  lli Solve(const int i, const int j, const int k, const int l) {
    if (i + j + k + l == 0) {
      // std::cout << "\t" << lol << "\n";
      return 1;
    }

    lli& ans = memo[i + j + k + l];
    if (ans != -1) return ans;

    ans = 0;
    if (i) {
      ans = Pref(i, j, k, l);
    } else if (j) {
      ans = Pref(i, j, k, l);
    } else if (k) {
      ans = Pref(i, j, k, l);
    } else {
      ans = Solve(0, 0, 0, 0);
    }

    return ans;
  }

  lli Solve2(const int i, const int j, const int k, const int l) {
    if (i + j + k + l == 0) {
      // std::cout << "\t" << lol << "\n";
      return 1;
    }

    lli ans = 0;
    if (i) {
      for (int f = 0; f <= j; ++f) {
        ans = (ans + combinatorics::StarsAndBars(i - 1, f) *
                         Solve2(0, j - f, k, l) % kMod) %
              kMod;
      }
    } else if (j) {
      for (int f = 0; f <= k; ++f) {
        ans = (ans + combinatorics::StarsAndBars(j - 1, f) *
                         Solve2(0, 0, k - f, l) % kMod) %
              kMod;
      }
    } else if (k) {
      for (int f = 0; f <= l; ++f) {
        ans = (ans + combinatorics::StarsAndBars(k - 1, f) *
                         Solve2(0, 0, 0, l - f) % kMod) %
              kMod;
      }
    } else {
      return ans = Solve2(0, 0, 0, 0);
    }

    return ans;
  }

  bool Run() {
    if (!(std::cin >> a >> b >> c >> d)) return false;

    memo.resize(4 * kMaxV + 1, -1);
    pref.resize(4 * kMaxV + 1, std::vector<lli>(4, -1));
    lli ans = Solve(a, b, c, d);
    std::cout << ans << "\n";
    // std::cout << "naive: " << Solve2(a, b, c, d) << "\n";

    return true;
  }
};
TestCase test_case;

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  combinatorics::Init();

  // std::cout << "2, 0: " << combinatorics::StarsAndBars(2, 0) << "\n";
  // std::cout << "2, 1: " << combinatorics::StarsAndBars(2, 1) << "\n";
  // std::cout << "2, 2: " << combinatorics::StarsAndBars(2, 2) << "\n";

  do {
    test_case = TestCase{};
  } while (test_case.Run());

  return 0;
}
