#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 100, maxX = 61; int n;
int a[maxN];

bool notPrime[maxX];
vector<int> primes;
int primeMask[maxX];

int memo[maxN][1<<17];
int chosen[maxN][1<<17];
int solve(int i = 0, int mask = 0)
{
  if (i == n) return 0;
  if (memo[i][mask] == -1)
  {
    int ans = solve(i + 1, mask) + (a[i] - 1), best = 1;
    for (int j = 2; j < maxX; j ++)
      if ((primeMask[j] & mask) == 0)
      {
        int got = solve(i + 1, mask | primeMask[j]) + abs(a[i] - j);
        if (got < ans)
          ans = got, best = j;
      }
    memo[i][mask] = ans, chosen[i][mask] = best;
  }
  return memo[i][mask];
}

int main()
{
  notPrime[0] = notPrime[1] = true;
  for (int i = 2; i < maxX; i ++)
  {
    if (!notPrime[i]) primes.push_back(i);
    for (int j = 0; i*primes[j] < maxX; j ++)
    {
      notPrime[i*primes[j]] = true;
      if (i % primes[j] == 0) break;
    }
  }
  for (int i = 1; i < maxX; i ++)
    for (int j = 0; j < primes.size() && primes[j] <= i; j ++)
      if (i % primes[j] == 0)
        primeMask[i] |= 1 << j;

  scanf("%d", &n);
  for (int i = 0; i < n; i ++)
    scanf("%d", &a[i]);

  memset(memo, -1, sizeof(memo));
  int cost = solve();
  DEBUG printf("%d\n", cost);
  for (int i = 0, mask = 0; i < n; i ++)
  {
    printf("%d%c", chosen[i][mask], i < n - 1 ? ' ' : '\n');
    mask |= primeMask[chosen[i][mask]];
  }

  return 0;
}