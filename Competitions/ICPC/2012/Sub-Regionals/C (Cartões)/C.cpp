#include <bits/stdc++.h>
#define lli long long int
using namespace std;

/* Tutorial:
  A DP with O(n²) memory is easy but won't get AC because it requires 800MB
  There's a way to reduce memory to O(n), but time complexity will remain O(n²)

  We're gonna process the values in blocks (n is even):
    for (int i = 0; i < n - 1; i ++)
      memo[i] = max(a[i], a[i + 1]);
    for (int blockSize = 4; blockSize <= n; blockSize += 2)
      for (int i = 0, j = blockSize - 1; j < n; i ++, j ++)
        memo[i] = max(a[i] + min(memo[i + 1], memo[i + 2]),
                      a[j] + min(memo[i], memo[i + 1]));
    ans = memo[0]

  Why?
  Suppose n == 2:
    ans = max(a[0], a[1]), easy
  Now n == 4:
    ans = max(a[0] + min(max(a[1], a[2]), max(a[2], a[3])),
              a[3] + min(max(a[0], a[1]), max(a[1], a[2])))
      Notice that: max(a[1], a[2]) == memo[1] and max(a[2], a[3]) == memo[2]
  Now n == 6:
    ans = max(a[0] + min(memo[1], memo[2]),
              a[5] + min(memo[0], memo[1]))
      Notice that memo[1] stores the best answer for the block [1, 2, 3, 4]
  ...
*/

const int maxN = 1e4; int n;
lli a[maxN], memo[maxN];

int main()
{
  while (scanf("%d", &n) != EOF)
  {
    for (int i = 0; i < n; i ++)
      scanf("%lld", &a[i]);

    for (int i = 0; i < n - 1; i ++)
      memo[i] = max(a[i], a[i + 1]);

    for (int blockSize = 4; blockSize <= n; blockSize += 2)
      for (int i = 0, j = blockSize - 1; j < n; i ++, j ++)
        memo[i] = max(a[i] + min(memo[i + 1], memo[i + 2]),
                      a[j] + min(memo[i], memo[i + 1]));
    printf("%lld\n", memo[0]);
  }
  return(0);
}