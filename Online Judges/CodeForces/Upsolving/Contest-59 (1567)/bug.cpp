#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const lli inf = 1e18;

// 2 - 3
// 3 - 6
// 4 - 10
// 5 - 15
lli comb(lli x)
{
  return x * (x + 1) >> 1;
}

const int maxN = 2e5; int n, q;
lli a[maxN];

int main()
{
  while (~scanf("%d %d", &n, &q))
  {
    for (int i = 0; i < n; i++)
      scanf("%lld", &a[i]);

    for (int i = 0; i < q; i++)
    {
      int op; scanf("%d", &op);
      if (op == 1)
      {
        int x; lli y; scanf("%d %lld", &x, &y); x--;
        a[x] = y;
      }
      else
      {
        int l, r; scanf("%d %d", &l, &r); l--, r--;
        lli ans = 0;
        for (int i = l; i <= r; i++)
        {
          int j = i;
          while (j + 1 <= r && a[j] <= a[j + 1]) j++;
          ans += comb(j - i + 1);
          // printf("%d %d - %lld %lld - %lld\n", i, j, a[i], a[j], comb(j - i + 1));
          i = j;
        }
        printf("%lld\n", ans);
      }
    }
  }
  return 0;
}
