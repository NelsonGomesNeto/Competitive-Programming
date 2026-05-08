#include <bits/stdc++.h>
#define DEBUG if (0)
#define lli long long int
#define ldouble long double
using namespace std;

/* Choose(n, k) = n! / (k! * (n - k)!)
  cases where n is too large, but close to k:
    Choose(n, k) = pi(k + 1 to n, i) / (n - k)!
  Pascal's Triangle:
    1      1      1      1      1
    1      2      3      4      5
    1      3      6     10
    1      4     10
    1      5
    1
    matrix(r, c) = Choose(r + c, c)
    (0-indexed)
*/

namespace combinatorics {
const lli kMod = 1e9 + 7;  // could be two as well
lli ModPow(lli x, lli y) {
  lli ans = 1;
  while (y) {
    if (y & 1LL) ans = ans * x % kMod;
    x = x * x % kMod, y >>= 1LL;
  }
  return ans;
}
lli Inv(lli x) { return ModPow(x, kMod - 2); }
const int kMaxX = 1e6 + 1;
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

int main() {
  combinatorics::Init();

  return 0;
}