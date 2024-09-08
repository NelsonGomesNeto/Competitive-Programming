#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxX = 1e5;
bool notPrime[maxX + 1];
vector<int> primes;
vector<pair<lli, int>> primeFactors[maxX + 1];

vector<pair<lli, int>> getPrimeFactors(lli num)
{
  if (num <= maxX) return primeFactors[num];
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

const int maxN = 1e5; int n, m;
int a[maxN];
bool has[maxN + 1];

int main()
{
  notPrime[0] = notPrime[1] = true;
  for (int i = 2; i <= maxX; i ++)
  {
    if (!notPrime[i]) primes.push_back(i), primeFactors[i].push_back({i, 1});
    for (int j = 0; i*primes[j] <= maxX; j ++)
    {
      notPrime[i*primes[j]] = true;
      int p = 0, num = i * primes[j];
      while (num % primes[j] == 0) num /= primes[j], p ++;
      primeFactors[i * primes[j]].push_back({primes[j], p});
      primeFactors[i * primes[j]].insert(primeFactors[i * primes[j]].end(), primeFactors[num].begin(), primeFactors[num].end());
      if (i % primes[j] == 0) break;
    }
  }

  while (~scanf("%d %d", &n, &m))
  {
    for (int i = 0; i < n; i++) scanf("%d", &a[i]);

    memset(has, false, sizeof(has));
    for (int i = 0; i < n; i++)
      for (auto &p: getPrimeFactors(a[i]))
        has[p.first] = true;

    vector<int> ans;
    for (int i = 1; i <= m; i++)
    {
      bool valid = true;
      for (auto &p: getPrimeFactors(i))
        if (has[p.first])
          valid = false;
      if (valid) ans.push_back(i);
    }

    printf("%d\n", (int)ans.size());
    for (int i: ans) printf("%d\n", i);
  }
  return 0;
}