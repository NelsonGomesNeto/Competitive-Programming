#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 1e6;
bool notPrime[maxN + 1];
vector<int> primes;

lli n, m, p;
bool check(lli i)
{
  if (p % i == 0)
  {
    lli j = p / i;
    if (p % j == 0)
    {
      lli a = i, b = j;
      if (a > b) swap(a, b);
      if (a <= n && b <= m)
        return true;
    }
  }
  return false;
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

  int t; scanf("%d", &t);
  for (int tt = 1; tt <= t; tt++)
  {
    scanf("%lld %lld %lld", &n, &m, &p);
    if (n > m) swap(n, m);

    bool can = false;
    for (int i = 1, end = sqrt(p); i <= end; i++)
      if (i <= n && p % i == 0)
      {
        int j = p / i;
        if (j <= m && p % j == 0)
          can = true;
      }

    printf("%s\n", can ? "YES" : "NO");
  }
  return 0;
}