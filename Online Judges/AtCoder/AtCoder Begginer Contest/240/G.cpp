#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 2e7 + 1, mid = 1e7;
lli n, x, y, z;
const lli mod = 998244353;
lli fat[mid + 1];

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
lli modInv(lli x)
{
  return modPow(x, mod - 2);
}

lli memo[maxN];
lli solve(int target, int i = 0, int x = 0)
{
  if (i == n) return x == target;
  lli &ans = memo[target - x + mid];
  if (ans != -1) return ans;
  return ans = (solve(target, i + 1, x + 1) + solve(target, i + 1, x - 1)) % mod;
}

int main()
{
  fat[0] = 1;
  for (int i = 1; i <= mid; i++)
    fat[i] = fat[i - 1] * i % mod;

  while (~scanf("%lld %lld %lld %lld", &n, &x, &y, &z))
  {
    int nn = n;
    n -= abs(x) + abs(y) + abs(z);
    memset(memo, -1, sizeof(memo));
    lli ans = solve(0) * fat[nn] % mod * modInv(2) % mod;
    printf("%lld\n", ans);
  }
  return 0;
}