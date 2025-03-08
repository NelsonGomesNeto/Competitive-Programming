#include <bits/stdc++.h>
#define DEBUG if (0)
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
      for (int j = 0, len2 = (len >> 1); j < len2; j++) {
        const std::complex<ldouble> u = a[i + j], v = a[i + j + len2] * w;
        a[i + j] = u + v;
        a[i + j + len2] = u - v;
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
const lli kRootPower = 1 << kPower;
void FindFirstPrimitiveRootOfPrimeMod() {
  lli r = 2;
  while (!(ModPow(r, kRootPower) == 1 && ModPow(r, 1 << (kPower - 1)) != 1))
    r++;
  std::println("valid: {}", r);
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

template <typename T>
std::string VectorToString(const std::vector<T>& arr) {
  std::ostringstream sout;
  for (int i = 0; i < arr.size(); i++) {
    if (i) sout << " ";
    sout << std::setprecision(7) << arr[i];
  }
  return sout.str();
}

int main() {
  int n, m;
  while (std::cin >> n >> m) {
    std::vector<int> a(n), b(m);
    for (int& ai : a) std::cin >> ai;
    for (int& bi : b) std::cin >> bi;

    std::vector<std::complex<ldouble>> fa(a.begin(), a.end()),
        fb(b.begin(), b.end());
    int n = 1;
    while (n < a.size() + b.size()) n <<= 1;
    fa.resize(n);
    fb.resize(n);

    convolution::FFT(fa, /*invert*/ false);
    std::println("roots: {}", VectorToString(fa));
    convolution::FFT(fb, /*invert*/ false);
    std::println("roots: {}", VectorToString(fb));

    const std::vector<ldouble> res_fft = convolution::MultiplyFFT(a, b);
    std::println("{}", VectorToString(res_fft));

    const std::vector<lli> res_ntt = convolution::MultiplyNTT(a, b);
    std::println("{}", VectorToString(res_ntt));
  }
  return 0;
}