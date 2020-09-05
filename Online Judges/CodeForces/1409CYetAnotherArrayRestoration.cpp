#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

int main()
{
  int t;
  while (scanf("%d", &t) != EOF)
    for (int tt = 0; tt < t; tt++)
    {
      lli n, x, y; scanf("%lld %lld %lld", &n, &x, &y);
      lli apart;
      for (apart = n - 1; apart >= 1; apart--)
        if ((y - x) % apart == 0)
          break;
      lli ans[n], toAdd = (y - x) / apart;
      int start;
      for (int i = n - 1; i >= 0; i--)
        if (y - i * toAdd >= 1)
        {
          start = i;
          break;
        }
      ans[start] = y;
      for (int i = start - 1; i >= 0; i--)
        ans[i] = ans[i + 1] - toAdd;
      for (int i = 1; i < n; i++)
        ans[i] = ans[i - 1] + toAdd;

      for (int i = 0; i < n; i++)
        printf("%lld%c", ans[i], i < n - 1 ? ' ' : '\n');
    }
  return 0;
}