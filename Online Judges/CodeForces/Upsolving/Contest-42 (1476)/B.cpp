#include <bits/stdc++.h>
#define DEBUG if(1)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 1e2; int n, k;
lli p[maxN];

int main()
{
  int t; scanf("%d", &t);
  for (int tt = 1; tt <= t; tt++)
  {
    scanf("%d %d", &n, &k);
    for (int i = 0; i < n; i++)
      scanf("%lld", &p[i]);

    lli total = p[0];
    lli ans = 0;
    for (int i = 1; i < n; i++)
    {
      lli change = p[i];

      lli lo = 0, hi = 1e12;
      while (lo < hi)
      {
        lli mid = (lo + hi) >> 1LL;
        lli aboveLeft = change * 100;
        lli aboveRight = k * (total + mid);
        if (aboveLeft <= aboveRight) hi = mid;
        else lo = mid + 1;
      }
      
      // DEBUG printf("\t\t%lld %lld\n", aboveLeft, aboveRight);
      // if (aboveLeft <= aboveRight) // safe
      // {
      // }
      // else
      // {
      //   lli delta = aboveLeft - aboveRight;
      //   ans += delta;
      //   total += delta;
      //   DEBUG printf("\t%d deu ruim %d\n", tt, i);
      // }
      ans += lo;
      total += lo;

      total += p[i];
    }
    printf("%lld\n", ans);
  }
  return 0;
}
