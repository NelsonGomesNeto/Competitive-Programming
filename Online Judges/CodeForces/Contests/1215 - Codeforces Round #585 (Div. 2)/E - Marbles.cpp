#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

/* Tutorial:
  maxA == 20 is very important because we can represent choices with a bitmask and try all

  Precalculate cost(i, j), which is:
    the number of movements required to move all i before j (inversion count)
      (if there're only i and j)
    This calculated adding the amount of j before each i

  Now, memo[bitmask] will store the minimum amount of moments if we'd chose
  the numbers setted in the bitmask. We start with bitmask = 0, memo[0] = 0, and:
  for each bitmask from 0 to (1 << 20) - 1:
    for each i (not present on the current bitmask):
      we try to put i in the beginning: (saving only the best)
      memo[bitmask | (1 << i)] = min(memo[bitmask | (1 << i)], memo[bitmask] + costSum)
      (costSum is calculated by adding the cost[i][j present on bitmask])
  ans = memo[(1 << 20) - 1]
*/

const int maxN = 4e5, maxA = 20; int n;
const lli inf = LLONG_MAX;
int a[maxN], cnt[maxN];
lli cost[maxA][maxA], memo[1 << maxA];

int main()
{
  while (scanf("%d", &n) != EOF)
  {
    memset(cnt, 0, sizeof(cnt)), memset(cost, 0, sizeof(cost));

    for (int i = 0; i < n; i ++)
    {
      scanf("%d", &a[i]); a[i] --;
      for (int j = 0; j < maxA; j ++)
        cost[a[i]][j] += cnt[j];
      cnt[a[i]] ++;
    }

    DEBUG {
      printf("     "); for (int i = 0; i < maxA; i ++) printf("%2d%c", i + 1, i < maxA - 1 ? ' ' : '\n');
      for (int i = 0; i < maxA; i ++)
      {
        printf("%2d - ", i + 1);
        for (int j = 0; j < maxA; j ++)
          printf("%2lld%c", cost[i][j], j < maxA - 1 ? ' ' : '\n');
      }
    }

    memo[0] = 0; for (int i = 1, end = 1 << maxA; i < end; i ++) memo[i] = inf;
    for (int bitmask = 0, end = 1 << maxA; bitmask < end; bitmask ++)
      for (int i = 0; i < maxA; i ++)
        if (!(bitmask & (1 << i)))
        {
          lli costSum = 0;
          for (int j = 0; j < maxA; j ++)
            if (bitmask & (1 << j))
              costSum += cost[i][j];
          memo[bitmask | (1 << i)] = min(memo[bitmask | (1 << i)], memo[bitmask] + costSum);
        }
    printf("%lld\n", memo[(1 << maxA) - 1]);
  }
  return 0;
}