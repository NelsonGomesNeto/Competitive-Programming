#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 1.4e5; int n, k;
int p[maxN];

int main()
{
  while (~scanf("%d %d", &n, &k))
  {
    for (int i = 0; i < n; ++i)
      scanf("%d", &p[i]);

    lli ans = 0;
    for (int i = 0; i < n; ++i)
    {
      int mi = p[i], mx = p[i];
      for (int j = i; j < n; ++j)
      {
        mi = min(mi, p[j]), mx = max(mx, p[j]);
        if (mx - mi <= j - i + k)
          ++ans;
      }
    }
    printf("%lld\n", ans);
  }
  return 0;
}