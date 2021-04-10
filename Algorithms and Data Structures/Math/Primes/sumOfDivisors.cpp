#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

/* Divisors Sum:
  Examples:
    4: 1 + 2 + 4 = 7
    5: 1 + 5 = 5
    30: 1 + 2 + 3 + 5 + 6 + 10 + 15 + 30 = 72

  The idea:
    Use all prime factors of n
    n = p_1^e_1 * p_2^e_2 * ... * p_k^e_k
    The sum of it's divisors is the sum of every possible of primes' powers
    Example:
      30 = 2^1 * 3^1 * 5^1
        sumOfDivisors(30) = (2^0 * 3^0 * 5^0)
          + (2^1 * 3^0 * 5^0) + (2^0 * 3^1 * 5^0) + (2^0 * 3^0 * 5^1)
          + (2^1 * 3^1 * 5^0) + (2^1 * 3^0 * 5^1) + (2^0 * 3^1 * 5^1)
          + (2^1 * 3^1 * 5^1)
    We can do that be simply multiplying the sum of each prime and it's powers:
      sumOfDivisors(n) = (p_1^0 + p_1^1 + ... p_1^e_1) * (p_2^0 + p_2^1 + ... p_2^e_2) * ... * (p_k^0 + p_k^1 + ... p_k^e_k)
      sumOfDivisors(30) = (2^0 + 2^1) * (3^0 + 3^1) (5^0 + 5^1)
*/

const int maxX = 1e7;
bool notPrime[maxX + 1];
vector<int> primes;
int divisorsSum[maxX + 1];

// Can count for every number in [1 : 1e14] (might go higher, but primes above 1e14 will fail)
lli getDivisorsSum(lli num)
{
  if (num <= maxX)
    return divisorsSum[num];

  lli res = 1;
  for (int p: primes)
  {
    if (p * p > num) break;

    lli sum = 1, pot = 1;
    while (num % p == 0)
    {
      num /= p;
      pot *= p;
      sum += pot;
    }
    res *= sum;
  }
  if (num >= 2)
    res *= num + 1;
  return res;
}

int main()
{
  for (int i = 1; i <= maxX; i ++)
    divisorsSum[i] = 1;

  notPrime[0] = notPrime[1] = true;
  for (int i = 2; i <= maxX; i ++)
  {
    if (!notPrime[i]) primes.push_back(i), divisorsSum[i] *= (i + 1);
    for (int j = 0; i*primes[j] <= maxX; j ++)
    {
      notPrime[i*primes[j]] = true;
      int p = 0, num = i * primes[j];
      int toAdd = 1, mul = 1;
      while (num % primes[j] == 0)
      {
        num /= primes[j], p++;
        mul *= primes[j];
        toAdd += mul;
      }
      divisorsSum[i * primes[j]] *= toAdd;
      divisorsSum[i * primes[j]] *= divisorsSum[num];
      if (i % primes[j] == 0) break;
    }
  }

  for (int i = 1; i <= 20; i++)
    printf("%d - %lld\n", i, getDivisorsSum(i));
  printf("%lld - %lld\n", (lli)1e14, getDivisorsSum((lli)1e14));
  return 0;
}