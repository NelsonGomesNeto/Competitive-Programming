#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 1e5; int n;
lli c[maxN];
lli a[maxN], b[maxN];

int main()
{
  int t; scanf("%d", &t);
  for (int tt = 1; tt <= t; tt++)
  {
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
      scanf("%lld", &c[i]);
    for (int i = 0; i < n; i++)
      scanf("%lld", &a[i]);
    for (int i = 0; i < n; i++)
      scanf("%lld", &b[i]);

    lli ans = 0, curr = 0;
    for (int i = 0; i + 1 < n; i++)
    {
      lli above = a[i + 1], below = b[i + 1];
      if (above < below)
        swap(above, below);

      if (i)
      {
        curr += below - 1 + 1;
        curr += c[i] - above + 1;
      }

      curr = max(curr, above - below + 1);

      DEBUG printf("\t%d %lld\n", i, curr);

      if (above == below) // closed the cycle
        curr = 1;

      ans = max(ans, curr + c[i + 1]);
    }

    printf("%lld\n", ans);
    // if (t != 1e3) printf("%lld\n", ans);
    // else if (tt == 134)
    // {
    //   printf("%d\n", n);
    //   for (int i = 0; i < n; i++)
    //     printf("%lld%c", c[i], i < n - 1 ? ' ' : '\n');
    //   for (int i = 0; i < n; i++)
    //     printf("%lld%c", a[i], i < n - 1 ? ' ' : '\n');
    //   for (int i = 0; i < n; i++)
    //     printf("%lld%c", b[i], i < n - 1 ? ' ' : '\n');
    // }
  }
  return 0;
}
