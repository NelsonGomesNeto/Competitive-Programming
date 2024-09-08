#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxX = 100;
bool composite[maxX + 1];
vector<int> allPrimes, primes;
lli n; int p;

lli solve2(lli curr = 1, int i = 0)
{
  if (curr > n) return 0;
  if (i == primes.size()) return 1;

  lli ans = solve2(curr, i + 1);
  while (curr < n)
  {
    curr *= primes[i];
    ans += solve2(curr, i + 1);
  }
  return ans;
}

vector<lli> half;

void solve(lli curr = 1, int i = 0)
{
  if (curr > n) return;
  if (i >= primes.size())
  {
    half.push_back(curr);
    return;
  }

  solve(curr, i + 2);
  while (curr < n)
  {
    curr *= primes[i];
    solve(curr, i + 2);
  }
}

int mergeSize(lli x, int lo = 0, int hi = half.size() - 1)
{
  while (lo < hi)
  {
    int mid = (lo + hi + 1) >> 1;
    if (half[mid] <= n / x) lo = mid;
    else hi = mid - 1;
  }
  return half[lo] <= n / x ? lo + 1 : -1;
}

lli solve3(lli curr = 1, int i = 1)
{
  if (curr > n) return 0;
  if (i >= primes.size())
    return mergeSize(curr);

  lli ans = solve3(curr, i + 2);
  while (curr < n)
  {
    curr *= primes[i];
    ans += solve3(curr, i + 2);
  }

  return ans;
}

int main()
{
  composite[0] = composite[1] = true;
  for (int i = 2; i <= maxX; ++i)
  {
    if (!composite[i])
      allPrimes.push_back(i);
    for (int j = 0; i * allPrimes[j] <= maxX; ++j)
    {
      composite[i * allPrimes[j]] = true;
      if (i % allPrimes[j] == 0)
        break;
    }
  }

  int tt = 0;
  while (~scanf("%lld %d", &n, &p))
  {
    half.clear();

    primes.clear();
    for (int pp : allPrimes)
      if (pp <= p)
        primes.push_back(pp);

    solve();
    sort(half.begin(), half.end());
    DEBUG {
      for (lli p : half)
        printf("\t%lld\n", p);
    }
    lli ans = solve3();

    printf("%lld\n", ans);
    DEBUG printf("\t%lld\n", solve2());
  }

  return 0;
}
