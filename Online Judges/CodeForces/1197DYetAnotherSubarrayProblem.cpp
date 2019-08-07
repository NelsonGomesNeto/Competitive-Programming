#include <bits/stdc++.h>
#define lli long long int
using namespace std;

/* Tutorial:
  The *m* being small is very important for the solution
  For each i, you will evaluate the block: [i, i + m - 1]
    (And basically run a Kadane over the array of blocks)
  So, there will be m kinds of blocks:
    Starting on: i % m == 0, i % m == 1, ..., i % m == m - 1
    Blocks that start on the same i % m can be "merged"
  There's only two options:
    To add the whole range to this i % m
    To stop adding at some position between [i, i + m - 1]
    Always saving the best possible
    (Don't forget to subtract k for each block)
*/

const int maxN = 3e5, maxM = 10; int n; lli m, k;
lli a[maxN], memo[maxM];

int main()
{
  while (scanf("%d %lld %lld", &n, &m, &k) != EOF)
  {
    memset(memo, 0, sizeof(memo));
    for (int i = 0; i < n; i ++)
      scanf("%lld", &a[i]);

    lli ans = 0;
    for (int i = 0; i < n; i ++)
    {
      lli sum = 0, best = 0;
      for (int j = 0; i + j < n && j < m; j ++)
      {
        sum += a[i + j];
        best = max(sum, best);
      }
      ans = max(ans, memo[i % m] + best - k);
      memo[i % m] = max(memo[i % m] + sum - k, 0LL);
    }
    printf("%lld\n", ans);
  }
  return(0);
}
