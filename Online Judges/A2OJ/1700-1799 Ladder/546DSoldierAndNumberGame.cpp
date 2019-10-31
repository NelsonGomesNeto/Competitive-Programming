#include <bits/stdc++.h>
#define DEBUG if(1)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 5e6 + 1; int a, b;
lli accSum[maxN + 1];

bool notPrime[maxN];
int divisors[maxN];
vector<int> primes;

int primeFactorization(int num)
{
  if (!notPrime[num]) return 1;
  int end = sqrt(num), pfp = 0;
  for (int p: primes)
  {
    if (p > end || p > num) break;
    while (num % p == 0) num /= p, pfp ++;
  }
  return pfp + (num > 1);
}

int main()
{
  notPrime[0] = notPrime[1] = true;
  for (int i = 2; i < maxN; i ++)
  {
    if (!notPrime[i]) primes.push_back(i), divisors[i] = 1;
    for (int j = 0; i * primes[j] < maxN; j ++)
    {
      notPrime[i * primes[j]] = true;
      int p = 0, num = i * primes[j];
      while (num % primes[j] == 0) num /= primes[j], p ++;
      divisors[i * primes[j]] += p + divisors[num];
      if (i % primes[j] == 0) break;
    }
  }
  for (int i = 1; i < maxN; i ++)
    accSum[i + 1] = accSum[i] + divisors[i];

  int t; scanf("%d", &t);
  while (t --)
  {
    scanf("%d %d", &a, &b);
    printf("%lld\n", accSum[a + 1] - accSum[b + 1]);
  }
  return 0;
}