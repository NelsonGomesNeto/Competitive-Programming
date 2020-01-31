#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 1e6 + 1; lli x;
const lli inf = 1000000000000LL;
bool notPrime[maxN + 1];
vector<int> primes;
vector<pair<lli, int>> primeFactors[maxN + 1];

vector<pair<lli, int>> getPrimeFactors(lli num)
{
  if (num <= maxN) return primeFactors[num];
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

int main()
{
  notPrime[0] = notPrime[1] = true;
  for (int i = 2; i <= maxN; i ++)
  {
    if (!notPrime[i]) primes.push_back(i), primeFactors[i].push_back({i, 1});
    for (int j = 0; i*primes[j] <= maxN; j ++)
    {
      notPrime[i*primes[j]] = true;
      int p = 0, num = i * primes[j];
      while (num % primes[j] == 0) num /= primes[j], p ++;
      primeFactors[i * primes[j]].push_back({primes[j], p});
      primeFactors[i * primes[j]].insert(primeFactors[i * primes[j]].end(), primeFactors[num].begin(), primeFactors[num].end());
      if (i % primes[j] == 0) break;
    }
  }

  while (scanf("%lld", &x) != EOF)
  {
    vector<pair<lli, int>> pf = getPrimeFactors(x);
    pf.push_back({1, 0}), pf.push_back({x, 0});
    DEBUG 
      for (auto &a: pf)
        printf("\t%lld\n", a.first);

    pair<lli, lli> ans = {inf, inf};
    for (auto &a: pf)
    {
      lli xx = x / a.first;
      for (lli j = 1, end = sqrt(xx); j <= end; j ++)
        if (xx % j == 0)
        {
          lli aa = a.first * j, bb = a.first * xx / j;
          if (lcm(aa, bb) != x) continue;
          DEBUG printf("\t%lld %lld %lld %lld %lld\n", a.first, xx, j, aa, bb);
          ans = max(aa, bb) < max(ans.first, ans.second) ? make_pair(aa, bb) : ans;
        }
    }

    if (ans.first > ans.second)
      swap(ans.first, ans.second);
    printf("%lld %lld\n", ans.first, ans.second);
  }

  return 0;
}
