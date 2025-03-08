#include <bits/stdc++.h>
#define DEBUG if (0)
#define DEBUG2 if (0)
#define lli long long int
#define ldouble long double

namespace convolution {
const ldouble kPi = std::acos(-1);

void FFT(std::vector<std::complex<ldouble>>& a, const bool invert) {
  const int n = (int)a.size();

  for (int i = 1, j = 0; i < n; i++) {
    int bit = n >> 1;
    for (; j & bit; bit >>= 1) j ^= bit;
    j ^= bit;

    if (i < j) std::swap(a[i], a[j]);
  }

  for (int len = 2; len <= n; len <<= 1) {
    ldouble ang = 2 * kPi / len * (invert ? -1 : 1);
    const std::complex<ldouble> wlen(std::cos(ang), std::sin(ang));
    for (int i = 0; i < n; i += len) {
      std::complex<ldouble> w(1);
      for (int j = 0; j < (len >> 1); j++) {
        const std::complex<ldouble> u = a[i + j], v = a[i + j + (len >> 1)] * w;
        a[i + j] = u + v;
        a[i + j + (len >> 1)] = u - v;
        w *= wlen;
      }
    }
  }

  if (!invert) return;
  for (std::complex<ldouble>& x : a) x /= n;
}

const lli kMod = 998244353LL;
lli ModPow(lli x, lli y) {
  lli ans = 1;
  while (y) {
    if (y & 1LL) ans = ans * x % kMod;
    x = x * x % kMod, y >>= 1LL;
  }
  return ans;
}
lli ModInv(const lli x) { return ModPow(x, kMod - 2); }
const lli kRoot = 31;
const lli kRootInv = ModInv(kRoot);
const lli kPower = __builtin_ctzll(kMod - 1);
const lli kRootPower = 1LL << kPower;
void FindFirstPrimitiveRootOfPrimeMod() {
  lli r = 2;
  while (!(ModPow(r, kRootPower) == 1 && ModPow(r, 1 << (kPower - 1)) != 1))
    r++;
  std::cout << "valid: " << r << "\n";
}
void NTT(std::vector<lli>& a, const bool invert) {
  const int n = (int)a.size();

  for (int i = 1, j = 0; i < n; i++) {
    int bit = n >> 1;
    for (; j & bit; bit >>= 1) j ^= bit;
    j ^= bit;

    if (i < j) std::swap(a[i], a[j]);
  }

  for (int len = 2; len <= n; len <<= 1) {
    lli wlen = invert ? kRootInv : kRoot;
    for (lli i = len; i < kRootPower; i <<= 1) wlen = wlen * wlen % kMod;

    for (int i = 0; i < n; i += len) {
      lli w = 1;
      for (int j = 0, len2 = (len >> 1); j < len2; j++) {
        const lli u = a[i + j], v = a[i + j + len2] * w % kMod;
        a[i + j] = u + v < kMod ? u + v : u + v - kMod;
        a[i + j + len2] = u - v >= 0 ? u - v : u - v + kMod;
        w = w * wlen % kMod;
      }
    }
  }

  if (!invert) return;
  const lli n_inv = ModInv(n);
  for (auto& x : a) x = x * n_inv % kMod;
}

template <typename I, typename C, typename O>
std::vector<O> Multiply(const std::vector<I>& a, const std::vector<I>& b,
                        std::function<void(std::vector<C>&, bool)> dft) {
  std::vector<C> fa(a.begin(), a.end()), fb(b.begin(), b.end());
  int n = 1;
  while (n < (int)(a.size() + b.size())) n <<= 1;
  fa.resize(n);
  fb.resize(n);

  dft(fa, /*invert=*/false);
  dft(fb, /*invert=*/false);
  if constexpr (std::is_same_v<C, lli>)
    for (int i = 0; i < n; i++) fa[i] = fa[i] * fb[i] % kMod;
  else
    for (int i = 0; i < n; i++) fa[i] *= fb[i];
  dft(fa, /*invert=*/true);

  std::vector<O> result(n);
  if constexpr (std::is_same_v<C, lli>)
    for (int i = 0; i < n; i++) result[i] = fa[i];
  else
    for (int i = 0; i < n; i++) result[i] = fa[i].real();
  return result;
}

template <typename I>
std::vector<lli> MultiplyNTT(const std::vector<I>& a, const std::vector<I>& b) {
  return Multiply<I, lli, lli>(a, b, NTT);
}
template <typename I>
std::vector<ldouble> MultiplyFFT(const std::vector<I>& a,
                                 const std::vector<I>& b) {
  return Multiply<I, std::complex<ldouble>, ldouble>(a, b, FFT);
}
}  // namespace convolution

const lli kMod = 998244353LL;
// const lli kMod = 1e18;
lli ModPow(lli x, lli y) {
  lli ans = 1;
  while (y) {
    if (y & 1LL) ans = ans * x % kMod;
    x = x * x % kMod, y >>= 1LL;
  }
  return ans;
}
lli ModInv(lli x) { return ModPow(x, kMod - 2); }

namespace combinatorics {
const int kMaxX = 4e5 + 1;
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
  for (int i = 0; i < kMaxX; i++) invFat[i] = ModInv(fat[i]);
}
}  // namespace combinatorics

int DigitCnt(lli x) {
  int cnt = x == 0;
  while (x) x /= 10, ++cnt;
  return cnt;
}

template <typename T>
std::string VectorToString(const std::vector<T>& arr) {
  std::ostringstream sout;
  for (int i = 0; i < arr.size(); ++i) {
    if (!sout.str().empty()) sout << " ";
    sout << arr[i];
  }
  return sout.str();
}

struct TestCase {
  int n;

  std::vector<int> cnt_by_size;
  std::vector<lli> sum_by_size;

  lli Naive() {
    std::vector<int> nums(n);
    for (int i = 0; i < n; ++i) nums[i] = i + 1;
    lli ans = 0, cnt = 0;
    do {
      int digits_before = 0;
      for (int i = n - 1; i >= 0; --i) {
        const lli res = ModPow(10, digits_before) * nums[i] % kMod;
        ans = (ans + res) % kMod;
        digits_before += DigitCnt(nums[i]);
      }
      ++cnt;
    } while (std::ranges::next_permutation(nums.begin(), nums.end()).found);
    return ans;
  }

  std::vector<lli> Mult(const std::vector<lli>& a, const std::vector<lli>& b) {
    // std::vector<lli> old_res(a.size() + b.size(), 0);
    // for (int i = 0; i < a.size(); ++i) {
    //   for (int j = 0; j < b.size(); ++j) {
    //     old_res[i + j] = (old_res[i + j] + a[i] * b[j] % kMod) % kMod;
    //   }
    // }

    const std::vector<lli> res = convolution::MultiplyNTT(a, b);
    return res;
  }

  lli Solve() {
    lli ans = 0;

    for (int to_pick = 1; to_pick < (int)cnt_by_size.size(); ++to_pick) {
      std::vector<std::vector<lli>> fk(cnt_by_size.size(), std::vector<lli>{});
      for (int k = 1; k < (int)cnt_by_size.size(); ++k) {
        const int group_size = cnt_by_size[k] - (to_pick == k);
        for (int j = 0; j <= group_size; ++j) {
          fk[k].push_back(combinatorics::Choose(group_size, j) *
                          ModPow(10, (lli)j * k) % kMod);
        }
      }

      std::vector<lli> poly = fk[1];
      for (int k = 2; k < (int)fk.size(); ++k) {
        poly = Mult(poly, fk[k]);
      }
      // std::println("poly: {}", VectorToString(poly));

      lli ans_at_pick = 0;
      for (int i = 0, end = std::min(n, (int)poly.size()); i < end; ++i) {
        const lli to_add = poly[i] * combinatorics::fat[i] % kMod *
                           combinatorics::fat[n - 1 - i] % kMod;
        ans_at_pick = (ans_at_pick + to_add) % kMod;
      }
      // assert(ans_at_pick >= 0 && sum_by_size[to_pick] >= 0);
      ans_at_pick = ans_at_pick * sum_by_size[to_pick] % kMod;

      ans = (ans + ans_at_pick) % kMod;
    }

    return ans;
  }

  bool Run() {
    if (!(std::cin >> n)) return false;

    cnt_by_size.resize(DigitCnt(n) + 1, 0);
    sum_by_size.resize(cnt_by_size.size(), 0);
    for (int i = 1; i <= n; ++i) {
      const int digit_cnt = DigitCnt(i);
      ++cnt_by_size[digit_cnt];
      sum_by_size[digit_cnt] = (sum_by_size[digit_cnt] + i) % kMod;
    }

    // std::cout << "\tnaive: " << Naive() << "\n";

    const lli ans = Solve();
    std::cout << ans << "\n";

    return true;
  }
};
TestCase test_case;

int main() {
  // std::ios::sync_with_stdio(false);
  // std::cin.tie(nullptr);

  // convolution::FindFirstPrimitiveRootOfPrimeMod();
  // return 0;

  combinatorics::Init();

  do {
    test_case = TestCase{};
  } while (test_case.Run());

  return 0;
}
