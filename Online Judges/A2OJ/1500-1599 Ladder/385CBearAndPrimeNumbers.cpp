#include <bits/stdc++.h>
#define lli long long int
using namespace std;

/* Tutorial:
  Use optimized sieve to find all primes
  Count the frequency of each number x
  Using sieve idea, notice that:
    f(p) = count[p*1] + count[p*2] + ... + count[p*k]
    Precalculate it and make an accumulated sum
*/

const int maxN = 1e6; int n;
const lli maxX = 1e7;
lli cnt[maxX + 1], f[maxX + 1], accSum[maxX + 2];
bool notPrime[maxX + 1];
vector<int> primes;

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

  scanf("%d", &n);
  for (int i = 0; i < n; i ++)
  {
    lli xx; scanf("%lld", &xx);
    cnt[xx] ++;
  }
  for (int &p: primes)
    for (int j = 1; p*j <= maxX; j ++)
      f[p] += cnt[p*j];
  for (int i = 0; i <= maxX; i ++) accSum[i + 1] = accSum[i] + f[i];

  int m; scanf("%d", &m);
  for (int i = 0; i < m; i ++)
  {
    lli l, r; scanf("%lld %lld", &l, &r);
    l = min(maxX, l); r = min(maxX, r);
    printf("%lld\n", accSum[r + 1] - accSum[l]);
  }

  return(0);
}