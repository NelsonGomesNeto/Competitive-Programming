#include <stdio.h>
#define lli long long int

#define MIN(a,b) (((a)<(b))?(a):(b))
#define MAX(a,b) (((a)>(b))?(a):(b))

int n, k;
int p[140000];

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
        mi = MIN(mi, p[j]), mx = MAX(mx, p[j]);
        if (mx - mi <= j - i + k)
          ++ans;
      }
    }
    printf("%lld\n", ans);
  }
  return 0;
}