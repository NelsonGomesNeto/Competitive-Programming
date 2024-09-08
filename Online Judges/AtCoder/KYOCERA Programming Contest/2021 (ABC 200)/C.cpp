#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 2e5; int n;
int a[maxN];
int cnt[maxN];

int main()
{
  while (~scanf("%d", &n))
  {
    memset(cnt, 0, sizeof(cnt));
    for (int i = 0; i < n; i++)
    {
      scanf("%d", &a[i]);
      a[i] %= 200;
      cnt[a[i]]++;
    }

    lli ans = 0;
    for (int i = 0; i < 200; i++)
      ans += (lli)cnt[i] * (cnt[i] - 1) >> 1LL;
    printf("%lld\n", ans);
  }
  return 0;
}