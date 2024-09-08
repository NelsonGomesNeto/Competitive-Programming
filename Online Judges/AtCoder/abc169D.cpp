#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 1e6;
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

  lli n;
  while (scanf("%lld", &n) != EOF)
  {
    vector<pair<lli, int>> pf = getPrimeFactors(n);
    lli ans = 0;
    bool had;
    set<lli> done;
    do
    {
      had = false;
      lli curr;
      for (auto &p: pf)
      {
        for (int j = 1; j <= p.second; j++)
        {
          curr = pow(p.first, j);
          if (!done.count(curr) && n % curr == 0)
          {
            had = true;
            break;
          }
        }
        if (had) break;
      }
      // printf("\t%lld - %lld\n", n, curr);
      if (had) done.insert(curr), ans++, n /= curr;
    }
    while (had);
    printf("%lld\n", ans);
  }

  return 0;
}