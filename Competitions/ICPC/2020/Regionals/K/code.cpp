#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxK = 750, maxN = 1e4; int k, n; lli l;
const lli mod = 1e9 + 7;
lli t[maxK][maxK], p[maxN];
int start[maxK][maxN], finish[maxK][maxN];

int binarySearch(int prv, int i, int ub)
{
  int lo = 0, hi = k - 1;
  while (lo < hi)
  {
    // printf("\t%d %d\n", lo, hi);
    int mid = (lo + hi + ub) >> 1;
    if (ub)
    {
      if (t[prv][mid] - l <= p[i]) lo = mid;
      else hi = mid - 1;
    }
    else
    {
      if (p[i] <= t[prv][mid] + l) hi = mid;
      else lo = mid + 1;
    }
  }
  if (t[prv][lo] - l <= p[i] && p[i] <= t[prv][lo] + l) return lo;
  return -1;
}

lli memo[maxK][maxN], pmemo[maxK + 1][maxN];
lli solve(int prv, int i);
lli pref(int prv, int i, int j = 0)
{
  if (j == k) return 0;
  lli &ans = pmemo[prv][i];
  if (ans != -1) return ans;
  ans = 0;
  if (t[prv][j] - l <= p[i] && p[i] <= t[prv][j] + l)
    ans = (ans + solve(j, i + 1)) % mod;
  ans = (ans + pref(prv, i, j + 1)) % mod;
  return ans;
}
lli solve(int prv, int i = 0)
{
  DEBUG printf("\t%d %d\n", prv, i);
  if (i >= n - 1) return 1;
  lli &ans = memo[prv][i];
  if (ans != -1) return ans;

  // ans = pref(prv, i);

  for (int j = 0; j < k; j++)
    if (t[prv][j] - l <= p[i] && p[i] <= t[prv][j] + l)
      ans = (ans + solve(j, i + 1)) % mod;
  return ans;
}

lli solve2()
{
  memset(memo, 0, sizeof(memo));
  memset(pmemo, 0, sizeof(pmemo));
  for (int prv = 0; prv < k; prv++) memo[prv][n - 1] = 1;

  for (int i = n - 2; i >= 0; i--)
  {
    for (int prv = 0; prv < k; prv++)
      if (start[prv][i] != -1)
      {
        // for (int j = start[prv][i]; j <= finish[prv][i]; j++)
        //   memo[prv][i] = (memo[prv][i] + memo[j][i + 1]) % mod;

        if (i == n - 2)
          memo[prv][i] = (finish[prv][i] - start[prv][i] + 1) % mod;
        else
          memo[prv][i] = (pmemo[finish[prv][i] + 1][i + 1] - pmemo[start[prv][i]][i + 1] + mod) % mod;
      }
      else
        memo[prv][i] = 0;

    for (int j = 0; j < k; j++)
      pmemo[j + 1][i] = (pmemo[j][i] + memo[j][i]) % mod;
  }

  lli ans = 0;
  for (int i = 0; i < k; i++)
    ans = (ans + memo[i][0]) % mod;
  return ans;
}

int main()
{
  while (~scanf("%d %lld", &k, &l))
  {
    for (int i = 0; i < k; i++)
      for (int j = 0; j < k; j++)
        scanf("%lld", &t[i][j]);

    scanf("%d", &n);
    for (int i = 0; i < n - 1; i++)
      scanf("%lld", &p[i]);

    memset(memo, -1, sizeof(memo));
    memset(pmemo, -1, sizeof(pmemo));
    memset(start, -1, sizeof(start));
    memset(finish, -1, sizeof(finish));

    for (int prv = 0; prv < k; prv++)
      for (int i = 0; i < n - 1; i++)
      {
        start[prv][i] = binarySearch(prv, i, 0);
        finish[prv][i] = binarySearch(prv, i, 1);
        DEBUG {
          printf("\t%d %d: ", i, prv);
          for (int j = 0; j < k; j++)
            printf("%d%c", t[prv][j] - l <= p[i] && p[i] <= t[prv][j] + l, j < k - 1 ? ' ' : '\n');
          printf("\t%d %d: ", i, prv);
          for (int j = 0; j < k; j++)
            printf("%d%c", p[i] <= t[prv][j] + l, j < k - 1 ? ' ' : '\n');
          printf("\t%d %d: ", i, prv);
          for (int j = 0; j < k; j++)
            printf("%d%c", t[prv][j] - l <= p[i], j < k - 1 ? ' ' : '\n');
          printf("\t\t%d %d - %d %d\n", prv, i, start[prv][i], finish[prv][i]);
        }
      }

    // lli ans = 0;
    // for (int i = 0; i < k; i++)
    //   ans = (ans + solve(i)) % mod;
    lli ans = solve2();
    printf("%lld\n", ans);
  }
  return 0;
}