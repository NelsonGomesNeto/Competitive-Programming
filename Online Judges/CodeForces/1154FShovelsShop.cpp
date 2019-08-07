#include <bits/stdc++.h>
using namespace std;

const int maxN = 2e5, maxM = 2e5, maxK = 2e3; int n, m, k;
int shovels[maxN], bestOffer[maxK + 1], accSum[maxK + 2];

int memo[maxK + 1];
int solve(int i = 0)
{
  if (i >= k) return(0);
  if (memo[i] == -1)
  {
    int ans = 1e9;
    for (int j = 1; j <= k - i; j ++)
      ans = min(ans, solve(i + j) + accSum[i + j] - accSum[i] - (bestOffer[j] ? accSum[i + bestOffer[j]] - accSum[i] : 0));
    memo[i] = ans;
  }
  return(memo[i]);
}

int main()
{
  scanf("%d %d %d", &n, &m, &k);
  for (int i = 0; i < n; i ++) scanf("%d", &shovels[i]);
  sort(shovels, shovels+n);
  for (int i = 0; i <= k; i ++) accSum[i + 1] = accSum[i] + shovels[i];
  for (int i = 0, amount, ith; i < m; i ++)
  {
    scanf("%d %d", &amount, &ith);
    if (amount > k) continue;
    bestOffer[amount] = max(bestOffer[amount], ith);
  }

  memset(memo, -1, sizeof(memo));
  int ans = solve();
  printf("%d\n", ans);

  return(0);
}