#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 1e5; int n; lli k;
char ans[maxN + 1];

int main()
{
  int t; scanf("%d", &t);
  while (t--)
  {
    scanf("%d %lld", &n, &k);
    for (int i = 0; i < n; i++)
      ans[i] = 'a';
    int lo = 0, hi = 1; lli now;
    for (now = 0; ; hi++)
    {
      lo = k - now - 1;
      if (lo == -1)
        lo = hi - 1;
      now += hi;
      if (now >= k)
        break;
    }
    DEBUG printf("%lld %lld %d\n", now, k, lo);
    ans[lo] = ans[hi] = 'b';
    reverse(ans, ans+n);
    ans[n] = '\0';
    printf("%s\n", ans);
  }
  return 0;
}