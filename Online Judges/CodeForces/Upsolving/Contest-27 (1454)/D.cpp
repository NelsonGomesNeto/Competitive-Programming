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

lli n;

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

  int t; scanf("%d", &t);
  for (int tt = 1; tt <= t; tt++)
  {
    scanf("%lld", &n);

    vector<pair<lli, int>> pf = getPrimeFactors(n);
    DEBUG {
      printf("%lld:\n", n);
      for (auto &p: pf)
        printf("\t%lld - %d\n", p.first, p.second);
    }

    vector<pair<int, lli>> fp;
    for (auto &p: pf)
      fp.push_back({p.second, p.first});
    sort(fp.begin(), fp.end(), greater<pair<int, lli>>());

    vector<lli> ans;
    lli curr = 1;
    for (int i = 0; i < fp[0].first - 1; i++)
    {
      ans.push_back(fp[0].second);
      curr *= fp[0].second;
    }
    ans.push_back(n / curr);
    printf("%d\n", (int)ans.size());
    for (int i = 0; i < ans.size(); i++)
      printf("%lld%c", ans[i], i < ans.size() - 1 ? ' ' : '\n');
  }
  return 0;
}
