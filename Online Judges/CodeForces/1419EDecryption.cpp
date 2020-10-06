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

  int t;
  while (scanf("%d", &t) != EOF)
    for (int tt = 1; tt <= t; tt++)
    {
      lli n; scanf("%lld", &n);
      vector<pair<lli, int>> pf = getPrimeFactors(n);

      vector<lli> divisors;
      for (int i = 1, end = sqrt(n); i <= end; i++)
        if (n % i == 0)
        {
          divisors.push_back(i);
          if (n % (n / i) == 0) divisors.push_back(n / i);
        }
      sort(divisors.begin(), divisors.end());
      divisors.resize(distance(divisors.begin(), unique(divisors.begin(), divisors.end())));

      set<lli> done;
      for (int i = 0; i < pf.size(); i++)
      {
        lli curr = pf[i].first, nxt = pf[(i + 1) % pf.size()].first;
        done.insert(curr), done.insert(curr * nxt);
      }

      vector<lli> ans;
      for (int i = 0; i < pf.size(); i++)
      {
        lli curr = pf[i].first, nxt = pf[(i + 1) % pf.size()].first;
        ans.push_back(curr);
        for (int d: divisors)
          if (d % curr == 0 && !done.count(d))
          {
            done.insert(d);
            ans.push_back(d);
          }
        if (pf.size() > 2 || i == pf.size() - 1)
          ans.push_back(curr * nxt);
      }

      int moves = 0;
      for (int i = 0; i < ans.size(); i++)
      {
        printf("%lld%c", ans[i], i < ans.size() - 1 ? ' ' : '\n');
        moves += gcd(ans[i], ans[(i + 1) % ans.size()]) == 1;
      }
      printf("%d\n", moves);

    }
  
  return 0;
}