#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxX = 5e6;
bool notPrime[maxX + 1];
vector<int> primes;
vector<pair<int, int>> primeFactors[maxX + 1];

vector<pair<int, int>> getPrimeFactors(lli num)
{
  if (num <= maxX) return primeFactors[num];
  vector<pair<int, int>> pf;
  for (int i: primes)
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

const int maxN = 1e5; int n;
map<int, lli> cnt;
struct Num
{
  int factors; lli freq; int value;
  bool operator<(const Num &other) const
  {
    return freq < other.freq;
  }
};
Num a[maxN];
lli aa[maxN];

map<int, lli> memo[maxN];
lli solve(int i = 0, int g = 0)
{
  if (i == n) return 0;
  if (memo[i].count(g)) return memo[i][g];
  lli &ans = memo[i][g];

  if (g == 0)
  {
    ans = max(solve(i + 1, aa[i]) + aa[i], solve(i + 1, 0) + 1);
  }
  else
  {
    lli gg = gcd(g, aa[i]);
    ans = max(solve(i + 1, gg) + gg, solve(i + 1, g) + 1);
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

  while (~scanf("%d", &n))
  {
    cnt.clear();
    for (int i = 0; i < n; i++)
    {
      scanf("%d", &a[i].value);
      memo[i].clear();
      vector<pair<int, int>> pf = getPrimeFactors(a[i].value);
      for (auto &p: pf)
        cnt[p.first] += pow(p.first, p.second);
    }
    for (int i = 0; i < n; i++)
    {
      vector<pair<int, int>> pf = getPrimeFactors(a[i].value);
      a[i].freq = 0;
      for (auto &p: pf)
        if (cnt[p.first])
          a[i].freq += cnt[p.first] - pow(p.first, p.second);
    }

    sort(a, a+n);
    reverse(a, a+n);
    for (int i = 0; i < n; i++)
      aa[i] = a[i].value;
    sort(aa+1, aa+n);
    reverse(aa+1, aa+n);

    lli ans = solve();
    printf("%lld\n", ans);
  }

  return 0;
}
