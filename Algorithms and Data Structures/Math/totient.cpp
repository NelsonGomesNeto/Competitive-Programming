#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

/* Euler's Totient function
  also known as Euler's Phi function

  phi(n) = integers [1, n] that are coprime with n
  phi(n) = gcd(i, n) == 1 for all i in [1, n]
*/

const int maxN = 1e6;
bool notPrime[maxN + 1];
vector<int> primes;
vector<pair<lli, int>> primeFactors[maxN + 1];

lli phi(lli number)
{
  lli ans = 1;
  if (number <= maxN)
    for (auto &p: primeFactors[number])
    {
      if (number % p.first) continue;
      // ans *= (p - 1) * p^(e - 1)
      number /= p.first, ans *= p.first - 1;
      while (number % p.first == 0)
        number /= p.first, ans *= p.first;
    }
  else
    for (int i = 2, end = sqrt(number); number >= i && i <= end; i ++)
    {
      if (number % i) continue;
      // ans *= (p - 1) * p^(e - 1)
      number /= i, ans *= i - 1;
      while (number % i == 0)
        number /= i, ans *= i;
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

  lli num;
  while (scanf("%lld", &num) != EOF)
    printf("phi(%lld) = %lld\n", num, phi(num));

  return 0;
}