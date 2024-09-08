#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

/*
     1 2 3 4 5 6 7 8 9 10
2 -> 2 4 6 8 10 | 5
3 -> 6 | 4
4 -> | 1
*/

const lli mod = 1e9 + 7;

const int maxX = 1e7;
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

  int t; scanf("%d", &t);
  for (int tt = 1; tt <= t; tt++)
  {
    lli n; scanf("%lld", &n);

    lli ans = n * pow((1 + sqrt(5)) / 2, 2);
    ans = ans % mod;
    printf("%lld\n", ans);
  }
  return 0;
}
