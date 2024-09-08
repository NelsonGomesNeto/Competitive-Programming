#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxX = 1e6;
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

const int maxN = 1e6; int n;
int a[maxN];
vector<pair<lli, int>> pf[maxN];

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

  while (scanf("%d", &n) != EOF)
  {
    for (int i = 0; i < n; i++)
    {
      scanf("%d", &a[i]);
      pf[i] = getPrimeFactors(a[i]);
    }

    map<int, int> cnt;
    for (int i = 0; i < n; i++)   
      for (auto &p: pf[i])
      {
        if (!cnt.count(p.first))
          cnt[p.first] = 0;
        cnt[p.first]++;
      }

    bool notCoprime = false;
    for (auto &c: cnt)
      if (c.second == n)
        notCoprime = true;
    if (notCoprime)
    {
      printf("not coprime\n");
      continue;
    }

    bool setWise = false;
    set<int> prv;
    for (int i = 0; i < n; i++)
    {
      for (auto &p: pf[i])
      {
        if (prv.count(p.first))
          setWise = true;
        prv.insert(p.first);
      }
    }
    printf("%s\n", setWise ? "setwise coprime" : "pairwise coprime");
  }

  return 0;
}