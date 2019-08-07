#include <bits/stdc++.h>
#define lli long long int
using namespace std;

const lli maxN = 1LL<<31 - 1, maxSqrt = 46350; lli n;
vector<lli> primes;
bool notPrime[maxSqrt];

lli phi(lli number)
{
  lli ans = 1;
  for (int i = 0, end = sqrt(number); number > 1 && primes[i] <= end; i ++)
  {
    if (number % primes[i]) continue;
    // ans *= (p - 1) * p^(e - 1)
    number /= primes[i], ans *= primes[i] - 1;
    while (number % primes[i] == 0)
      number /= primes[i], ans *= primes[i];
  }
  if (number > 1) ans *= number - 1;
  return(ans);
}

int main()
{
  notPrime[0] = notPrime[1] = true;
  for (int i = 2; i < maxSqrt; i ++)
  {
    if (!notPrime[i]) primes.push_back(i);
    for (int j = 0; i * primes[j] < maxSqrt; j ++)
    {
      notPrime[i * primes[j]] = true;
      if (i % primes[j] == 0) break;
    }
  }

  while (scanf("%lld", &n) != EOF && n)
    printf("%lld\n", phi(n) >> 1LL);
  return(0);
}