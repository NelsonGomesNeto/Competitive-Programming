#include <bits/stdc++.h>
#define DEBUG if(1)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 1e6;
bool notPrime[maxN + 1];
vector<int> primes;
vector<pair<lli, int>> primeFactors[maxN + 1];

lli a, m;
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
  for (int i = 2; i <= maxN; i ++)
  {
    if (!notPrime[i]) primes.push_back(i), primeFactors[i].push_back({i, 1});
    for (int j = 0; i*primes[j] <= maxN; j ++)
    {
      notPrime[i*primes[j]] = true;
      int p = 0, num = i * primes[j];
      while (num % primes[j] == 0) num /= primes[j], p ++;
      primeFactors[i * primes[j]].push_back({primes[j], p});
      primeFactors[i * primes[j]].insert(primeFactors[i * primes[j]].end(), primeFactors[num].begin(), primeFactors[num].end());
      if (i % primes[j] == 0) break;
    }
  }

  int t; scanf("%d", &t);
  while (t --)
  {
    scanf("%lld %lld", &a, &m);
    printf("%lld\n", phi(m / gcd(a, m)));
  }
  return 0;
}