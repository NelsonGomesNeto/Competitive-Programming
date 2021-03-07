#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

int main()
{
  int t; scanf("%d", &t);
  for (int tt = 1; tt <= t; tt++)
  {
    int n; scanf("%d", &n);
    lli h[n]; for (int i = 0; i < n; i++) scanf("%lld", &h[i]);

    bool can = true;
    lli curr = 0;
    for (int i = 0; i < n; i++)
    {
      lli left = i;
      if (left >= h[i])
      {
        curr -= left - h[i];
        can &= curr >= 0;
      }
      else
        curr += h[i] - left;
      h[i] = left;
    }
    printf("%s\n", can ? "YES" : "NO");
  }
  return 0;
}
