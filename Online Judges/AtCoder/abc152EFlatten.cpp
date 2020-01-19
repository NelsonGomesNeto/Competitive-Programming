#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 1e4, maxNum = 1e6; int n;
const lli mod = 1e9 + 7;
int a[maxN];
bool notPrime[maxNum + 1];
vector<int> primes;
vector<pair<lli, int>> primeFactors[maxNum + 1];

vector<pair<lli, int>> getPrimeFactors(lli num)
{
  if (num <= maxNum) return primeFactors[num];
  vector<pair<lli, int>> pf;
  for (lli i: primes)
  {
    if (i > num) break;
    if (num % i == 0)
    {
      int p = 0;
      while (num % i == 0) num /= i, p ++;
      pf.push_back({i, p});
    }
  }
  if (num != 1)
    pf.push_back({num, 1});
  return pf;
}

lli modPow(lli x, lli y)
{
  lli ans = 1;
  while (y)
  {
    if (y & 1LL) ans = (ans * x) % mod;
    x = (x * x) % mod, y >>= 1LL;
  }
  return ans;
}
lli inv(lli x)
{
  return modPow(x, mod - 2);
}

int main()
{
  notPrime[0] = notPrime[1] = true;
  for (int i = 2; i <= maxNum; i ++)
  {
    if (!notPrime[i]) primes.push_back(i), primeFactors[i].push_back({i, 1});
    for (int j = 0; i*primes[j] <= maxNum; j ++)
    {
      notPrime[i*primes[j]] = true;
      int p = 0, num = i * primes[j];
      while (num % primes[j] == 0) num /= primes[j], p ++;
      primeFactors[i * primes[j]].push_back({primes[j], p});
      primeFactors[i * primes[j]].insert(primeFactors[i * primes[j]].end(), primeFactors[num].begin(), primeFactors[num].end());
      if (i % primes[j] == 0) break;
    }
  }

  while (scanf("%d", &n) != EOF)
  {
    for (int i = 0; i < n; i ++)
      scanf("%d", &a[i]);

    int l[primes.size()]; memset(l, 0, sizeof(l));
    for (int i = 0; i < n; i ++)
    {
      vector<pair<lli, int>> pf = getPrimeFactors(a[i]);
      for (auto &p: pf)
      {
        int pos = lower_bound(primes.begin(), primes.end(), p.first) - primes.begin();
        l[pos] = max(l[pos], p.second); 
      }
    }

    lli modLcm = 1;
    for (int i = 0; i < primes.size(); i ++)
      modLcm = modLcm * modPow(primes[i], l[i]) % mod;

    lli ans = 0;
    for (int i = 0; i < n; i ++)
      ans = (ans + modLcm * inv(a[i])) % mod;

    printf("%lld\n", ans);
  }
  return 0;
}