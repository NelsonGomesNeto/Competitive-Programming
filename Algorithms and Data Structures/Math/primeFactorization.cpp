#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 1e6;
bool notPrime[maxN + 1];
vector<int> primes;

vector<pair<lli, int>> getPrimeFactors(lli num)
{
  vector<pair<lli, int>> primeFactors;
  for (lli i: primes)
  {
    if (i > num) break;
    if (num % i == 0)
    {
      int p = 0;
      while (num % i == 0) num /= i, p ++;
      primeFactors.push_back({i, p});
    }
  }
  if (num != 1)
    primeFactors.push_back({num, 1});
  return primeFactors;
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