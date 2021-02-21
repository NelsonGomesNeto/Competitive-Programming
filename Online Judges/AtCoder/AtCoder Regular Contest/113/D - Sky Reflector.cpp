#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxX = 1e6 + 1;
const lli mod = 998244353;

lli fat[maxX], invFat[maxX];
lli modPow(lli x, lli y)
{
  lli ans = 1;
  while (y)
  {
    if (y & 1LL) ans = ans * x % mod;
    x = x * x % mod, y >>= 1LL;
  }
  return ans;
}
lli inv(lli x)
{
  return modPow(x, mod - 2);
}
lli choose(lli nn, lli kk)
{
  if (nn < kk) return 0;
  if (nn < mod) return fat[nn] * invFat[kk] % mod * invFat[nn - kk] % mod;
  lli ans = 1;
  while (nn || kk)
  {
    lli nnn = nn % mod, kkk = kk % mod;
    nn /= mod, kk /= mod;
    ans = ans * choose(nnn, kkk) % mod;
  }
  return ans;
}
// nn = stars, kk = bars
lli starsAndBars(lli nn, lli kk)
{
  return choose(nn + kk, kk);
}

const int maxN = 2e5;
int n, m, k;

/*
A[i] = min(mat[i][:])
B[j] = max(mat[:][j])

Notice that max(A) <= min(B)

Now, for each x = [1 : k], we calculate how many A and B we can make
  A count: x^n - (x - 1)^n
    all arrays with range 1 : x (MINUS) all arrays where max(A) < x
  B count: (k - x + 1)^m
    all arrays with range x : k
Multiply A count with B count and add through 1 to k

min(n, m) = 1 cases must be handled separately
  ans = modPow(k, max(n, m))
*/

int main()
{
  fat[0] = 1;
  for (lli i = 1; i < maxX; i++)
    fat[i] = i * fat[i - 1] % mod;
  for (int i = 0; i < maxX; i++)
    invFat[i] = inv(fat[i]);

  while (~scanf("%d %d %d", &n, &m, &k))
  {
    lli ans = 0;
    for (int x = 1; x <= k; x++)
    {
      // max(A) <= i
      // min(B) >= i
      lli acnt = (modPow(x, n) - modPow(x - 1, n) + mod) % mod;
      lli bcnt = modPow(k - x + 1, m);
      ans = (ans + acnt * bcnt % mod) % mod;
    }

    if (n == 1 || m == 1)
      ans = modPow(k, max(n, m));

    printf("%lld\n", ans);
  }
  return 0;
}