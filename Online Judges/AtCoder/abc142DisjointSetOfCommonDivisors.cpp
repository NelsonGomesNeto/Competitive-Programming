#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 1e6;
bool notPrime[maxN + 1];
vector<lli> primes;

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

  lli a, b; scanf("%lld %lld", &a, &b);
  list<lli> primeFactors = getPrimeFactors(__gcd(a, b));
  printf("%d\n", (int) primeFactors.size() + 1);

  return 0;
}
