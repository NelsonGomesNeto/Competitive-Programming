#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 100; int n;
ldouble p[maxN];

int main()
{
  while (scanf("%d", &n) != EOF)
  {
    for (int i = 0; i < n; i ++)
      scanf("%Lf", &p[i]);
    sort(p, p+n, greater<ldouble>());

    ldouble once = p[0], never = 1 - p[0];
    for (int i = 1; i < n; i ++)
    {
      ldouble newOnce = never*p[i] + once*(1 - p[i]), newNever = never*(1 - p[i]);
      if (newOnce > once)
        once = newOnce, never = newNever;
    }
    printf("%.10Lf\n", once);
  }

  return 0;
}