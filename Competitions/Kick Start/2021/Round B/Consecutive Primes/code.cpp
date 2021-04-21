#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxX = 1e9 + 1e8;
bitset<maxX + 1> notPrime;
deque<int> primes;

int main()
{
  notPrime[0] = notPrime[1] = true;
  for (int i = 2; i <= maxX; i ++)
  {
    if (!notPrime[i]) primes.push_back(i);
    for (int p: primes)
    {
      lli res = (lli)i*p;
      if (res > maxX) break;
      notPrime[res] = true;
      if (i % p == 0) break;
    }
  }

  int t; scanf("%d", &t);
  for (int tt = 1; tt <= t; tt++)
  {
    lli z; scanf("%lld", &z);
    int lo = 0, hi = primes.size() - 2;
    while (lo < hi)
    {
      int mid = (lo + hi + 1) >> 1;
      if ((lli)primes[mid] * primes[mid + 1] <= z) lo = mid;
      else hi = mid - 1;
    }
    printf("Case #%d: %lld\n", tt, (lli)primes[lo] * primes[lo + 1]);
  }

  return 0;
}