#include <bits/stdc++.h>
using namespace std;

/* Tutorial:
  Remember, you have to do a circle
  Count the frequency of each number
  for i in [1 : 200000]:
    if (cnt[i]):
      Since we have to make a circle, you have to be able to come back
      Therefore, to be part of the circle starting from i, every number
      must have cnt[number] > 1 (the last one can be cnt[number] == 1)
      After reaching the last number:
        save the begin and end of this circle (if it's bigger than the best)
        and set i to the last, since every number from this circle, will
        end up at the same last number (therefore, having a smaller size)
  Printing the answer is easy, read my code below
*/

const int maxN = 2e5; int n;
int a[maxN], cnt[maxN + 1];

int main()
{
  scanf("%d", &n);
  for (int i = 0; i < n; i ++)
  {
    scanf("%d", &a[i]);
    cnt[a[i]] ++;
  }

  int ans = 0, bestLo = 1, bestHi = 1, lo = 1, hi = 1;
  for (int i = 1; i <= maxN; i ++)
    if (cnt[i])
    {
      lo = i, hi = i; int sum = cnt[hi];
      while (hi + 1 <= maxN && cnt[hi + 1] > 1) sum += cnt[++ hi];
      if (hi + 1 <= maxN && cnt[hi + 1] == 1) sum += cnt[++ hi];
      if (sum > ans)
        ans = sum, bestLo = lo, bestHi = hi;
      i = hi - (lo < hi);
    }
  // printf("%d %d %d\n", ans, bestLo, bestHi);

  printf("%d\n", ans);
  for (int i = bestLo; i <= bestHi; i ++)
    for (int j = cnt[i] >> 1; j > 0; j --)
      printf("%d ", i);
  for (int i = bestHi; i >= bestLo; i --)
    for (int j = (cnt[i] >> 1) + (cnt[i] & 1); j > 0; j --)
      printf("%d ", i);
  printf("\n");

  return(0);
}