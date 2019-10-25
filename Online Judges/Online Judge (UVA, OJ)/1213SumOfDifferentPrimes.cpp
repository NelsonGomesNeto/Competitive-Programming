#include <bits/stdc++.h>
#define lli long long int
using namespace std;
int n, k;
vector<int> primes;
lli dp[1121][15][187];

lli solve(int sum, int i, int done)
{
  if (i == k) return(sum == n);
  if (done < primes.size() && sum + primes[done] > n) return(0);

  if (dp[sum][i][done] == -1)
  {
    for (int j = done; j < primes.size() && sum + primes[j] <= n; j ++)
      dp[sum][i][done] += solve(sum + primes[j], i + 1, j + 1);
    dp[sum][i][done] ++;
  }
  return(dp[sum][i][done]);
}

int main()
{
  int sieve[1121]; memset(sieve, 0, sizeof(sieve));
  sieve[0] = sieve[1] = 1;
  for (int i = 2; i < 1121; i ++)
    for (int j = 2; i * j < 1121; j ++)
      sieve[i * j] = 1;
  for (int i = 0; i < 1121; i ++) if (!sieve[i]) primes.push_back(i);

  while (scanf("%d %d", &n, &k) && !(!n && !k))
  {
    memset(dp, -1, sizeof(dp));
    lli ans = solve(0, 0, 0);
    printf("%lld\n", ans);
  }
  return(0);
}
