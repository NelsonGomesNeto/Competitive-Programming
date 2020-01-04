#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 2e5; int n; lli k;
lli a[maxN], acc[maxN + 1];

int main()
{
  while (scanf("%d %lld", &n, &k) != EOF)
  {
    for (int i = 0; i < n; i ++)
    {
      scanf("%lld", &a[i]);
      acc[i + 1] = (acc[i] + a[i] - 1) % k;
    }

    map<lli, lli> cnt;
    cnt[0] = 1;
    lli ans = 0;
    for (int i = 1; i <= n; i ++)
    {
      if (i >= k) cnt[acc[i - k]] --;
      if (!cnt.count(acc[i]))
        cnt[acc[i]] = 0;
      ans += cnt[acc[i]] ++;
    }

    printf("%lld\n", ans);
  }
  return 0;
}