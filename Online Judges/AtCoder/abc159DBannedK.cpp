#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 2e5; int n;
int a[maxN]; lli cnt[maxN + 1];

int main()
{
  int t = 0;
  while (scanf("%d", &n) != EOF)
  {
    if (t++) printf("--------\n");
    memset(cnt, 0, sizeof(cnt));
    for (int i = 0; i < n; i++)
    {
      scanf("%d", &a[i]);
      cnt[a[i]]++;
    }

    lli ans = 0;
    for (int i = 1; i <= n; i++)
      ans += cnt[i] * (cnt[i] - 1) >> 1LL;

    for (int i = 0; i < n; i++)
    {
      lli rem = cnt[a[i]] * (cnt[a[i]] - 1) >> 1LL;
      lli add = (cnt[a[i]] - 1) * (cnt[a[i]] - 2) >> 1LL;
      printf("%lld\n", ans - rem + add);
    }
  }
  return 0;
}