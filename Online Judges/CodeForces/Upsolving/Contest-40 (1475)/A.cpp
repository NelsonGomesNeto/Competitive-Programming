#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 1e7;
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
    lli n; scanf("%lld", &n);
    while (!(n & 1LL))
      n >>= 1LL;
    bool can = n > 1 && n & 1LL;
    printf("%s\n", can ? "YES" : "NO");
  }
  return 0;
}
