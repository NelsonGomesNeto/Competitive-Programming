#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

/*
  if x > y:
    gcd(x, y) = gcd(x - y, y)

  So, if a pair of numbers isn't coprime (gcd(x, y) != 1):
    Their gcd is bounded by x - y

  In this case, x - y will be at most 72.
  There are exactly 20 primes <= 72.

  So we can just run a bistmask DP using the primes <= 72 each number has:
    ans = solve(i + 1, mask) + !(mask & primesMask[i])*solve(i + 1, mask | primesMask[i])

  O(n * 2^pi(n))
  Where pi(n) == number of primes <= n
*/

const int maxX = 72, maxPrimes = 20;
bool notPrime[maxX + 1];
vector<lli> primes;

const int maxN = 72;
lli a, b; int n;
int primesMask[maxN + 1];
int memo[maxN + 1][1LL << maxPrimes];
int solve(int i = 0, int mask = 0)
{
  if (i == n + 1)
    return 1;
  int &ans = memo[i][mask];
  if (ans != -1)
    return ans;

  ans = solve(i + 1, mask);
  if (!(mask & primesMask[i]))
    ans += solve(i + 1, mask | primesMask[i]);
  return ans;
}

int main()
{
  notPrime[0] = notPrime[1] = true;
  for (int i = 2; i <= maxX; i ++)
  {
    if (!notPrime[i]) primes.push_back(i);
    for (int j = 0; i*primes[j] <= maxX; j ++)
    {
      notPrime[i*primes[j]] = true;
      if (i % primes[j] == 0) break;
    }
  }

  while (~scanf("%lld %lld", &a, &b))
  {
    n = b - a;
    for (lli i = a; i <= b; i++)
    {
      primesMask[i - a] = 0;
      for (int j = 0; j < primes.size(); j++)
      {
        int p = primes[j];
        if (i % p == 0)
          primesMask[i - a] |= (1LL << j);
      }
    }

    memset(memo, -1, sizeof(memo));
    int ans = solve();
    printf("%d\n", ans);
  }
  return 0;
}