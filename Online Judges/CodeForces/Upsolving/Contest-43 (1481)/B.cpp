#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 1e2; int n; lli k;
int h[maxN];

int main()
{
  int t; scanf("%d", &t);
  for (int tt = 1; tt <= t; tt++)
  {
    scanf("%d %lld", &n, &k);
    for (int i = 0; i < n; i++)
      scanf("%d", &h[i]);

    int ans = -1;
    while (k > 0)
    {
      int i = 0;
      while (i + 1 < n && h[i] >= h[i + 1]) i++;

      if (i == n - 1)
      {
        ans = -1;
        break;
      }

      int delta = 1;
      k -= delta;
      h[i] += delta;
      if (k <= 0)
        ans = i + 1;
    }
    DEBUG {
      printf("\t");
      for (int i = 0; i < n; i++)
        printf("%d%c", h[i], i < n - 1 ? ' ' : '\n');
    }
    printf("%d\n", ans);
  }
  return 0;
}
