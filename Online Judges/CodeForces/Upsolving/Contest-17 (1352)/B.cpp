#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

int main()
{
  int t; scanf("%d", &t);
  while (t--)
  {
    lli n; int k; scanf("%lld %d", &n, &k);
    if (k == 1) printf("YES\n%lld\n", n);
    else
    {
      lli base = n / (k - 1);
      bool can = false;
      for (int i = 0; i <= 10 && base; i++, base--)
      {
        lli rem = n - base * (k - 1);
        if (rem <= 0) continue;
        if ((rem & 1) == (base & 1))
        {
          printf("YES\n");
          for (int i = 0; i < k - 1; i++) printf("%lld ", base);
          printf("%lld\n", rem);
          can = true;
          break;
        }
      }
      if (!can)
        printf("NO\n");
    }
  }
  return 0;
}
