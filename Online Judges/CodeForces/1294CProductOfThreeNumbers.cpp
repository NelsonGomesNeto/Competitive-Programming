#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 1e6; lli n;
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

  int t; scanf("%d", &t);
  for (int tt = 0; tt < t; tt ++)
  {
    scanf("%lld", &n); lli nn = n;
    vector<pair<lli, int>> pf = getPrimeFactors(n);

    lli a = pf[0].first;
    n /= a;
    pf = getPrimeFactors(n);
    lli b = pf.size() > 1 ? pf[1].first : !pf.empty() ? (pf[0].first == a ? pf[0].first * pf[0].first : pf[0].first) : 1;
    n /= b;
    lli c = n;
    // printf("%lld %lld %lld\n", a, b, c);
    if (a < 2 || b < 2 || c < 2 || a * b * c != nn || a == b || a == c || b == c)
      printf("NO\n");
    else
      printf("YES\n%lld %lld %lld\n", a, b, c);
  }

  return 0;
}
