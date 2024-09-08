#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

/*
  for all letters: cnt[letter] % k == 0
*/

const lli mod = 1e9 + 7;

const int maxX = 2e5;
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

const int maxN = 2e5;
int n, q;
lli a[maxN];

map<lli, int> pfs[maxN];
int total[maxX + 1], accSub[maxX + 1];
map<int, int> toSub[maxX + 1];
int ptr[maxX + 1];

lli modPow(lli x, lli y)
{
  lli ans = 1;
  while (y)
  {
    if (y & 1LL) ans = ans * x % mod;
    x = x * x % mod, y >>= 1LL;
  }
  return ans;
}

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

  while (~scanf("%d %d", &n, &q))
  {
    memset(total, 0, sizeof(total));
    for (int i = 0; i <= maxX; i++)
      toSub[i].clear(), pfs[i].clear();
    memset(accSub, 0, sizeof(accSub));

    for (int i = 0; i < n; i++)
    {
      scanf("%lld", &a[i]);
      for (auto &[p, pot]: getPrimeFactors(a[i]))
      {
        total[p]++;
        if (!toSub[p].count(pot + 1))
          toSub[p][pot + 1] = 0;
        toSub[p][pot + 1]++;

        pfs[i][p] = pot;
      }
    }

    lli ans = 1;
    for (int p: primes)
    {
      ptr[p] = 1;
      while (true)
      {
        if (!toSub[p].count(ptr[p]))
          toSub[p][ptr[p]] = 0;
        if (total[p] - accSub[p] - toSub[p][ptr[p]] == n)
        {
          accSub[p] += toSub[p][ptr[p]];
          ptr[p]++;
          ans = ans * p % mod;
        }
        else
          break;
      }
    }

    for (int qq = 0; qq < q; qq++)
    {
      int i; lli x; scanf("%d %lld", &i, &x); i--;

      for (auto &[p, pot]: getPrimeFactors(x))
      {
        if (!pfs[i].count(p))
          pfs[i][p] = 0, total[p]++;
        else
          toSub[p][pfs[i][p] + 1]--;

        pfs[i][p] += pot;
        pot = pfs[i][p];

        DEBUG printf("\t%lld %d\n", p, pot);

        if (!toSub[p].count(pot + 1))
          toSub[p][pot + 1] = 0;
        toSub[p][pot + 1]++;

        while (true)
        {
          if (!toSub[p].count(ptr[p]))
            toSub[p][ptr[p]] = 0;

          DEBUG printf("\t\t%d %d %d\n", total[p], accSub[p], toSub[p][ptr[p]]);
          if (total[p] - accSub[p] - toSub[p][ptr[p]] == n)
          {
            accSub[p] += toSub[p][ptr[p]];
            ptr[p]++;
            ans = ans * p % mod;
          }
          else
            break;
        }
      }

      printf("%lld\n", ans);
    }
  }
  return 0;
}
