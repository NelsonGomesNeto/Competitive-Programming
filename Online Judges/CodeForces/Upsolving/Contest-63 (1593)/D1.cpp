#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 40; int n;
lli a[maxN];

int main()
{
  int t; scanf("%d", &t);
  for (int tt = 1; tt <= t; tt++)
  {
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
      scanf("%lld", &a[i]);

    if (*max_element(a, a+n) == *min_element(a, a+n))
      printf("-1\n");
    else
    {
      lli g = -1;
      for (int i = 0; i < n; i++)
        for (int j = i + 1; j < n; j++)
        {
          lli aa = a[i], bb = a[j];
          lli delta = abs(aa - bb);
          if (g == -1) g = delta;
          else g = gcd(g, delta);
        }
      printf("%lld\n", g);
    }
  }
  return 0;
}
