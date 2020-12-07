#include <bits/stdc++.h>
#define lli long long int
using namespace std;

/* Tutorial:
  First, how can calculate the cost from i to j in O(1)? (i <= j)
    It's the sum of the submatrix from (i, i) to (j, j): (Use accumulated sum)
      sum[j][j] - sum[i - 1][j] - sum[j][i - 1] + sum[i - 1][i - 1]

  The easy recurrence equation is:
    dp[i][j] = min(dp[i - 1][t] + cost(t + 1, j) for all t in [1, j])
      i = the amount of gondolas available
      j = the amount of fox in the queue
      cost(x, y) calculates the cost of all foxes from x to y together
    You can fill it in O(k*n^2), but it won't pass the time limit

  Notice that the recurrence equation fits the DP optimization by Divide and Conquer case
  The only missing part to check is: opt[i][j] <= opt[i][j + 1] for all j
    In other words, if the the best choice of t for i gondolas and j foxes will
    always be less than or equal to the best choice for i gondolas and j + 1 foxes
    Which is true

  I recomend solving the base case (n == 1) first, since it will always be cost(1, j)
  Look at my solve function to understand better the optimization
  Notice that it will find the best splitting point (optj) to with mid foxes
  Now, when finding solution to (lo, mid - 1), we know that the upper limit is optj
  Similarly, to (mid + 1, hi), we know that the lower bound limit is optj
    (So the search space will narrow more and more)
    (Also, the maximum iterations will be n per level, and there will be lg(n) levels)
  With this, we've reduced from O(k*n^2) to O(k*n*lg(n))
*/

const int maxN = 4e3 + 1, maxK = 800 + 1, inf = 1e9; int n, k;
int cost[maxN][maxN];

int getCost(int i, int j)
{
  return cost[j][j] - cost[i - 1][j] - cost[j][i - 1] + cost[i - 1][i - 1];
}

int memo[maxK][maxN];
void solve(int i, int lo = 1, int hi = n, int optlo = 1, int opthi = n)
{
  if (lo > hi) return;

  int mid = (lo + hi) >> 1, optj = optlo;
  memo[i][mid] = inf;
  for (int j = optlo, end = min(mid - 1, opthi); j <= end; j ++)
    if (memo[i - 1][j] + getCost(j + 1, mid) < memo[i][mid])
      memo[i][mid] = memo[i - 1][j] + getCost(j + 1, mid), optj = j;

  solve(i, lo, mid - 1, optlo, optj);
  solve(i, mid + 1, hi, optj, opthi);
}

int main()
{
  scanf("%d %d\n", &n, &k);
  for (int i = 1; i <= n; i ++)
    for (int j = 1; j <= n; j ++)
    {
      char num, sep; scanf("%c%c", &num, &sep);
      cost[i][j] = num - '0';
    }

  for (int i = 1; i <= n; i ++)
  {
    for (int j = 1; j <= n; j ++)
      cost[i][j] += cost[i][j - 1] + cost[i - 1][j] - cost[i - 1][j - 1];
    memo[1][i] = getCost(1, i);
  }

  for (int i = 2; i <= k; i ++)
    solve(i);
  printf("%d\n", memo[k][n] >> 1);

  return(0);
}
