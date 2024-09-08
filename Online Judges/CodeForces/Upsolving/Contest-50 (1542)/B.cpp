#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

/*
a, (b + 1), a * (b + 1), 2*b + 1, a^2, a * (2*b + 1)
*/

int main()
{
  int t; scanf("%d", &t);
  for (int tt = 1; tt <= t; tt++)
  {
    lli n, a, b; scanf("%lld %lld %lld", &n, &a, &b);
    bool can = false;
    lli curr = 1;
    while (curr < n)
    {
      lli delta = n - curr;
      if (delta % b == 0)
        can = true;

      if (a == 1) break;
      curr *= a;
    }
    can |= curr == n;

    printf("%s\n", can ? "Yes" : "No");
  }
  return 0;
}
