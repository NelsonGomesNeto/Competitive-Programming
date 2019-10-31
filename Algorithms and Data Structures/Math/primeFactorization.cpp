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
  for (int i = 1; i <= maxN; i ++)
    if (primeFactors[i] != getPrimeFactors(i))
      printf("Failed %d\n", i);

  int n; scanf("%d", &n);
  for (int i = 0; i < n; i ++)
  {
    lli num; scanf("%lld", &num);
    vector<pair<lli, int>> pf = getPrimeFactors(num);
    printf("%lld:", num);
    for (auto &p: pf) printf(" %lld^%d", p.first, p.second);
    printf("\n");
  }

  return 0;
}