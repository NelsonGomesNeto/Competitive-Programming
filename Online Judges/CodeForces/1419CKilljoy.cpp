#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 1e3; int n, x;
int a[maxN];

int main()
{
  int t;
  while (scanf("%d", &t) != EOF)
  {
    for (int tt = 1; tt <= t; tt++)
    {
      scanf("%d %d", &n, &x);
      bool noX = true;
      for (int i = 0; i < n; i++)
      {
        scanf("%d", &a[i]);
        if (a[i] == x)
          noX = false;
      }

      int ans = 0;
      if (!(*min_element(a, a+n) == x && *max_element(a, a+n) == x))
      {
        lli delta = 0;
        for (int i = 0; i < n; i++)
          if (a[i] != x)
          {
            delta += x - a[i];
            a[i] = x;
          }
        ans = 1 + (delta != 0 && noX);
      }
      printf("%d\n", ans);
    }
  }
  return 0;
}
