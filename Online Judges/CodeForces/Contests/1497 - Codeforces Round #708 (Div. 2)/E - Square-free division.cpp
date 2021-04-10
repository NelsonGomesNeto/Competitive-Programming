#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

/* Tutorial:
  It's strongly recommended that you first try to solve E1 (greedy)

  First notice that two numbers (x and y) will lead to a perfect square iff
  the prime powers are even:
    x * y = p_1^e_1 * p_2^e_2 * ... * p_m^e_m
      where p_i is the i-th prime factor of x * y
      and e_i the power the i-th prime factor is in x * y
    x * y is a perfect square iff e_i is even for all i

  So, if a prime factor of x is even: we can simply ignore it
  And if it's odd: we use it (notice that we only the prime, not prime^something)
  Applying above's logic, we can transform a[i] into mask(a[i]), where mask(a[i])
  is a number with the prime factors with odd powers.

  With that, if mask(a[i]) == mask(a[j]): a[i] * a[j] is a perfect square


  Now, for the problem:
    minimize the amount of contiguos sequences with no masks repeating
      and you can change at most k numbers
  Actually, once you change a number: it will be better to make it different from any
  other, so you might see "change a number" as "remove a number" or even "at most
  k repeating numbers (considering all contiguous sequences)"

  It will always be optimal to make the biggest sequence possible. But we can
  change some of them and we don't know when is the best moment to do so.

  So, if we are at position i and have u usable changes:
  We can go to: (rightMost(i)with(kk)changes + 1) and lose kk changes
  So:
    ans[i][usable] = min{1 + solve(maxRight[i][kk] + 1, usable - kk), for kk in [0 : usable]}
    (I did it TopDown, but BottomUp is doable)

  We just need to know what is the rightMost for each i with kk changes (greedy).
    We don't need to calculate for all i, just the positions we want.
*/

const int maxX = 1e7;
bool notPrime[maxX + 1];
vector<int> primes;
int getMissingPrimeFactors(int num)
{
  int pp = 1;
  for (int i: primes)
  {
    if (i > num) break;
    if (!notPrime[num])
    {
      pp *= num;
      return pp;
    }
    if (num % i == 0)
    {
      int p = 0;
      while (num % i == 0) num /= i, p++;
      if (p & 1)
        pp *= i;
    }
  }
  if (num != 1)
    pp *= num;
  return pp;
}

const int maxN = 2e5, maxK = 20; int n, k;
const int inf = 1e7;
int a[maxN];
int misa[maxN];

// maxRight[i][kk] = rightmost position (r) where [i : r] has at most kk repeated elements
// i.e. used kk changes
bool toVisit[maxN], has[maxX + 1];
int maxRight[maxN][maxK + 1];
int memo[maxN][maxK + 1];
int solve(int i, int usable)
{
  if (i == n)
    return 0;
  int &ans = memo[i][usable];
  if (ans != -1)
    return ans;

  ans = inf;
  for (int kk = 0; kk <= usable; kk++)
  {
    assert(maxRight[i][kk] != -1);
    ans = min(ans, 1 + solve(maxRight[i][kk] + 1, usable - kk));
  }
  return ans;
}

int main()
{
  notPrime[0] = notPrime[1] = true;
  for (int i = 2; i <= maxX; i++)
  {
    if (!notPrime[i]) primes.push_back(i);
    for (int j = 0; (lli)i*primes[j] <= maxX; j++)
    {
      notPrime[i*primes[j]] = true;
      if (i % primes[j] == 0) break;
    }
  }

  int t;
  while (~scanf("%d", &t))
  {
    for (int tt = 1; tt <= t; tt++)
    {
      scanf("%d %d", &n, &k);
      for (int i = 0; i < n; i++)
      {
        scanf("%d", &a[i]);
        misa[i] = getMissingPrimeFactors(a[i]);
      }

      DEBUG {
        printf("missing: ");
        for (int i = 0; i < n; i++)
          printf("%d%c", misa[i], i < n - 1 ? ' ' : '\n');
      }

      for (int i = 0; i < n; i++)
        for (int kk = 0; kk <= k; kk++)
          maxRight[i][kk] = -1;

      for (int i = 0; i < n; i++)
      {
        toVisit[i] = false;
        has[misa[i]] = false;
      }
      toVisit[0] = true;
      for (int i = 0; i < n; i++)
        if (toVisit[i])
        {
          int j = i, newi;
          for (int kk = 0; kk <= k; kk++)
          {
            while (j < n && !has[misa[j]])
              has[misa[j++]] = true;

            maxRight[i][kk] = j - 1;
            if (j < n)
            {
              toVisit[j] = true;
              j++;
            }
          }

          for (int jj = i; jj <= j; jj++)
            has[misa[jj]] = false;
        }

      DEBUG {
        printf("   ");
        for (int kk = 0; kk <= k; kk++)
          printf("%2d%c", kk, kk < k ? ' ' : '\n');
        for (int i = 0; i < n; i++)
        {
          printf("%2d ", i);
          for (int kk = 0; kk <= k; kk++)
            printf("%2d%c", maxRight[i][kk], kk < k ? ' ' : '\n');
        }
      }

      for (int i = 0; i < n; i++)
        for (int kk = 0; kk <= k; kk++)
          memo[i][kk] = -1;
      int ans = inf;
      for (int kk = 0; kk <= k; kk++)
        ans = min(ans, 1 + solve(maxRight[0][kk] + 1, k - kk));
      printf("%d\n", ans);
    }
  }

  return 0;
}
