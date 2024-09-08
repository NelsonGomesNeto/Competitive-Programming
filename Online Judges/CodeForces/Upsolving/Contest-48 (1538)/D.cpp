#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

lli a, b, k;

vector<lli> getDivisors(lli num)
{
  vector<lli> divisors;
  for (int i = 2, end = sqrt(num); i <= end; i++)
    if (num % i == 0)
    {
      divisors.push_back(i);
      if (num % (num / i) == 0 && num / i != i)
        divisors.push_back(num / i);
    }
  if (num > 1) divisors.push_back(num);
  sort(divisors.begin(), divisors.end());
  return divisors;
}
int cnt(lli num)
{
  int total = 0;
  for (int i = 2, end = sqrt(num); i <= end && i <= num; i++)
    while (num % i == 0)
      num /= i, total++;
  return total + (num > 1);
}
vector<lli> adiv, bdiv;

struct State
{
  lli aa, bb, kk;
  bool operator<(const State &other) const { return aa < other.aa || (aa == other.aa && bb < other.bb) || (aa == other.aa && bb == other.bb && kk < other.kk); }
};
map<State, bool> memo;
bool solve(lli aa = a, lli bb = b, lli kk = k)
{
  if (kk == 0) return aa == bb;
  if (aa > bb) swap(aa, bb);

  State curr{aa, bb, kk};
  if (memo.count(curr)) return memo[curr];

  for (lli d: adiv)
  {
    if (d > aa) break;
    if (aa % d == 0 && solve(aa / d, bb, kk - 1))
      return memo[curr] = true;
  }
  for (lli d: bdiv)
  {
    if (d > bb) break;
    if (bb % d == 0 && solve(aa, bb / d, kk - 1))
      return memo[curr] = true;
  }

  return memo[curr] = false;
}

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
    scanf("%lld %lld %lld", &a, &b, &k);

    bool can = true;
    lli g = gcd(a, b);
    if (cnt(a / g) + cnt(b / g) + 2*cnt(g) >= k)
    {
      if (k < 5)
      {
        adiv = getDivisors(a), bdiv = getDivisors(b);
        can = solve();
      }
    }
    else
    {
      if (k <= 5)
      {
        adiv = getDivisors(a), bdiv = getDivisors(b);
        can = solve();
      }
      else can = false;
    }

    if (can) printf("YES\n");
    else printf("NO\n");
    // getPrimeFactors(b);

    // if (cnt(a) + cnt(b) < k)
    // {
    //   printf("NO\n");
    //   continue;
    // }

    // adiv = getDivisors(a), bdiv = getDivisors(b);
    // int ans = solve();
    // printf("%s\n", ans ? "YES" : "NO");
  }
  return 0;
}
