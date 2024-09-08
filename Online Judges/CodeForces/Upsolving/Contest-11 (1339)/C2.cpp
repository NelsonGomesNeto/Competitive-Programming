#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 1e5; int n;
const lli maxX = 3e9;
lli a[maxN];

int main()
{
  int t; scanf("%d", &t);
  while (t--)
  {
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
      scanf("%lld", &a[i]);

    int ans = 0; lli mx = a[0];
    for (int i = 1, j = n - 1; i < n; i++)
    {
      lli diff = mx - a[i];
      if (diff > 0)
      {
        int o = 0;
        while (diff) diff >>= 1, o++;
        ans = max(ans, o);
      }
      mx = max(mx, a[i]);
    }
    printf("%d\n", ans);
  }
  return 0;
}