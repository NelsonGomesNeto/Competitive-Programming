#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxX = 1e6;
bool composite[maxX + 1];
vector<int> primes;
vector<lli> pp;

const lli maxN = 1e12;
lli n;

int main()
{
  composite[0] = composite[1] = true;
  for (int i = 2; i <= maxX; ++i)
  {
    if (!composite[i])
    {
      primes.push_back(i);
      pp.push_back((lli)primes.back() * primes.back());
    }
    for (int j = 0; i * primes[j] <= maxX; ++j)
    {
      composite[i * primes[j]] = true;
      if (i % primes[j] == 0)
        break;
    }
  }

  while (~scanf("%lld", &n))
  {
    lli ans = 0;
    for (int ai = 0; ai < primes.size(); ++ai)
    {
      lli limit = n / pp[ai];
      int startCi = [ai, limit]()
      {
        int lo = ai + 1, hi = primes.size() - 1;
        while (lo < hi)
        {
          int mid = (lo + hi + 1) >> 1;
          if (pp[mid] < limit) lo = mid;
          else hi = mid - 1;
        }
        return pp[lo] < limit ? lo : -1;
      }();

      for (int ci = startCi; ci > ai + 1; --ci)
      {
        lli acLimit = limit / pp[ci];
        int lo = ai + 1, hi = ci - 1;
        while (lo < hi)
        {
          int mid = (lo + hi + 1) >> 1;
          if (primes[mid] <= acLimit) lo = mid;
          else hi = mid - 1;
        }
        int total = primes[lo] <= acLimit ? lo - (ai + 1) + 1 : 0;
        DEBUG printf("\t\t%d\n", total);
        ans += total;
      }
    }
    printf("%lld\n", ans);
  }
  return 0;
}
