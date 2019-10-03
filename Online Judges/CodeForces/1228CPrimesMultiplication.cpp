#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 1e6;
const lli mod = 1e9 + 7;
bool notPrime[maxN + 1];
vector<int> primes;

lli x, n;

list<lli> getPrimeFactors(lli num)
{
  list<lli> primeFactors;
  for (lli i: primes)
  {
    if (i > num) break;
    if (num % i == 0)
    {
      primeFactors.push_back(i);
      while (num % i == 0) num /= i;
    }
  }
  if (num != 1)
    primeFactors.push_back(num);
  return primeFactors;
}

lli modMult(lli x, lli y, lli m = mod)
{
  // printf("%lld %lld %lld\n", x, y, m);
  lli ans = 0;
  while (y)
  {
    if (y & 1LL) ans = (ans + x) % m;
    x = (x + x) % m, y >>= 1LL;
  }
  return ans;
}
lli modExp(lli x, lli y)
{
  lli ans = 1;
  while (y)
  {
    if (y & 1LL) ans = modMult(ans, x);
    x = modMult(x, x), y >>= 1LL;
  }
  return ans;
}

int main()
{
  notPrime[0] = notPrime[1] = true;
  for (int i = 2; i <= maxN; i ++)
  {
    if (!notPrime[i]) primes.push_back(i);
    for (int j = 0; i*primes[j] <= maxN; j ++)
    {
      notPrime[i*primes[j]] = true;
      if (i % primes[j] == 0) break;
    }
  }

  scanf("%lld %lld", &x, &n);
  list<lli> p = getPrimeFactors(x);
  lli ans = 1;
  for (lli i: p)
  {
    lli at = i;
    // printf("here %lld\n", at);
    list<lli> a;
    while (at <= n && (a.empty() || at > a.back()))
    {
      // printf("\there %lld\n", at);
      a.push_back(at);
      at *= i;
      // if (at >= (n >> 1)) break;
    }
    reverse(a.begin(), a.end());
    lli rem = 0;
    for (lli j: a)
    {
      // printf("%lld %lld\n", n / j, rem);
      ans = modMult(ans, modExp(j, n / j - rem));
      // ans = ans * modExp(j, n / j - rem) % mod;
      rem += n / j - rem;
    }
  }
  printf("%lld\n", ans);

  return 0;
}
