#include <stdio.h>
#define lli long long int

int n, m;
lli a[2000];

int main()
{
  while (scanf("%d %d", &n, &m) != EOF)
  {
    for (int i = 0; i < n; i ++)
    {
      scanf("%lld", &a[i]);
      a[i] %= m;
    }
    int q; scanf("%d", &q);
    while (q --)
    {
      int l, r, d; scanf("%d %d %d", &l, &r, &d); l --, r --;
      int ans = 0;
      for (int i = l; i <= r; i ++)
        ans += a[i] == d;
      printf("%d\n", ans);
    }
  }
}