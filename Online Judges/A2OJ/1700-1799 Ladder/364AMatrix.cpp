#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

/* Tutorial:
  Notice that sum(i1, j1, i2, j2) == sum(i1, j1) * sum(i2, j2)
  We can also calculate the maximum unidimensional sum: 9*4000
  Count the frequency of each sum (using accumulated sum)

  Now, for each sum: ans += cnt[sum] * cnt[a / sum]
    Be careful to handle, sum == 0, a % sum != 0 and a / sum > maxSum
  BUT, there's a corner case: a == 0
    In this case: ans += cnt[0] * cnt[0] + 2 * cnt[0] * (sum(cnt[x]) for x in [1 : maxSum])
*/

const int maxN = 4e3 + 2, maxX = 9*4e3 + 1; int n;
lli a, accSum[maxN], cnt[maxX];
char s[maxN];

int main()
{
  scanf("%lld", &a);
  scanf(" %s", s); n = strlen(s);
  for (int i = 0; i < n; i ++)
    accSum[i + 1] = (s[i] - '0') + accSum[i];

  DEBUG for (int i = 0; i < n; i ++)
    for (int j = 0; j < n; j ++)
      printf("%d%c", (s[i] - '0') * (s[j] - '0'), j < n - 1 ? ' ' : '\n');

  for (int i = 0; i < n; i ++)
    for (int j = i; j < n; j ++)
      cnt[accSum[j + 1] - accSum[i]] ++;

  lli ans = 0;
  if (a)
  {
    for (int sum = 1; sum < maxX; sum ++)
      if (a % sum == 0 && a / sum < maxX)
        ans += cnt[sum] * cnt[a / sum];
  }
  else
  {
    ans += cnt[0] * cnt[0];
    for (int sum = 1; sum < maxX; sum ++)
      ans += cnt[0] * cnt[sum] * 2LL;
  }

  printf("%lld\n", ans);

  return 0;
}