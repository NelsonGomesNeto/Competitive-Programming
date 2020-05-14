#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

/* Tutorial:
  The core idea is to count how many times each gcd will happen
  Notice that gcd == k will only happen once
  Expanding that, gcd == g will happen at most (k / g)^n times. In the case
  where there's no other multiple of g <= k: we will have 1^n. In the case
  there's another one, we will have: 2^n - (how many times that other multiple
  happened (which is 1^n))

  So, we can count how many time each gcd happened from k to 1 using their multiples:
  for (g = k; g >= 1; k--)
  {
    ans[g] = (k / g)^n; (for this gcd, we have k / g options of numbers)
    for (j = 2; j * g <= k; j++)
      ans[g] -= ans[j * g]; (but we can't consider the times in which the choice
      of the numbers will lead to another gcd; this will only happen for multiples
      of g)
  }
*/

const int maxN = 1e5;
lli ans[maxN + 1];
const lli mod = 1e9 + 7;

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

int main()
{
  int n, k;
  while (scanf("%d %d", &n, &k) != EOF)
  {
    for (int i = k; i >= 1; i--)
    {
      ans[i] = modPow(k / i, n);
      for (int j = 2; i * j <= k; j++)
        ans[i] = (ans[i] - ans[i * j] + mod) % mod;
    }
    for (int i = 1; i <= k; i++)
      ans[i] = ans[i] * i % mod;

    lli total = 0;
    for (int i = 1; i <= k; i++)
      total = (total + ans[i]) % mod;
    printf("%lld\n", total);
  }
  return 0;
}