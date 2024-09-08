#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 3e5; int n[3];
lli a[3][maxN];
lli sums[3];

int main()
{
  while (~scanf("%d %d %d", &n[0], &n[1], &n[2]))
  {
    memset(sums, 0, sizeof(sums));
    for (int i = 0; i < 3; i++)
    {
      for (int j = 0; j < n[i]; j++)
      {
        scanf("%lld", &a[i][j]);
        sums[i] += a[i][j];
      }
      sort(a[i], a[i]+n[i]);
    }
    lli totalSum = sums[0] + sums[1] + sums[2];

    lli toRemove = LONG_LONG_MAX;
    for (int i = 0; i < 3; i++)
    {
      lli curr = sums[i];
      for (int j = 0; j < 3; j++)
        if (i != j)
          curr = min(curr, a[i][0] + a[j][0]);
      toRemove = min(toRemove, 2LL * curr);
    }

    lli ans = totalSum - toRemove;
    printf("%lld\n", ans);
  }
  return 0;
}
