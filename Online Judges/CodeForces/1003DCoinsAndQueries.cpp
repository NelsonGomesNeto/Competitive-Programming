#include <bits/stdc++.h>
#define DEBUG if(0)
using namespace std;
#define lli long long int
unordered_map<lli, lli> dp;

int main()
{
  int n, q; scanf("%d %d", &n, &q);
  lli a[n]; for (int i = 0; i < n; i ++) scanf("%lld", &a[i]);
  sort(a, a+n);

  while (q --)
  {
    lli query; scanf("%lld", &query);
    int amount = 0, qq = query, now = n;
    // if (!dp.count(qq))
    // {
      do
      {
        int pos = lower_bound(a, a+now, query) - a;
        pos = min(pos, now - 1);
        while (pos > -1 && a[pos] > query) pos --;
        if (pos < 0) { amount = -1; break; }
        int divi = query / a[pos];
        if (divi > 1)
        {
          int low = lower_bound(a, a+now, a[pos]) - a;
          int quantity = min(pos - low + 1, divi);
          now = pos - quantity + 1; amount += quantity;
          query -= quantity * a[pos];
        }
        else
        {
          now = pos; amount ++;
          query -= a[pos];
        }
        DEBUG printf("%d %lld %lld\n", pos, a[pos], query);
      } while(query);
    //   dp[qq] = amount;
    // }
    // printf("%lld\n", dp[qq]);
    printf("%d\n", amount);
  }
  return(0);
}