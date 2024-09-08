#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 1e6;
bool notPrime[maxN + 1];
vector<int> primes;

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

  int t; scanf("%d", &t);
  for (int tt = 1; tt <= t; tt++)
  {
    int d; scanf("%d", &d);
    lli ans = 1;
    for (int i = 0, m = 1; i < 3; i++)
    {
      ans *= m;
      m += d;
      m = *upper_bound(primes.begin(), primes.end(), m - 1);
    }

    DEBUG {
      vector<int> divisors;
      for (int i = 1, sq = sqrt(ans); i <= sq; i++)
      {
        if (ans % i == 0)
        {
          divisors.push_back(i);
          if (ans % (ans / i) == 0)
            divisors.push_back(ans / i);
        }
      }

      sort(divisors.begin(), divisors.end());
      divisors.resize(distance(divisors.begin(), unique(divisors.begin(), divisors.end())));
      for (int i = 0; i < divisors.size(); i++)
        printf("\t%d\n", divisors[i]);
      for (int i = 1; i < divisors.size(); i++)
        if (divisors[i] - divisors[i - 1] < d)
          printf("DEU RUIM\n");
    }

    printf("%lld\n", ans);
  }
  return 0;
}
