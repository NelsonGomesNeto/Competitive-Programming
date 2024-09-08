#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

int main()
{
  int n, x;
  while (~scanf("%d %d", &n, &x))
  {
    int a[n];
    for (int i = 0; i < n; i++)
      scanf("%d", &a[i]);

    int ans = 0;
    for (int s = 0; s < n; s++)
    {
      int cnt = 1;
      for (int i = s; i + 1 < n; i++)
      {
        if (a[i + 1] - a[i] <= x)
          cnt++;
        else
          break;
      }
      ans = max(ans, cnt);
    }
    printf("%d\n", ans);
  }
  return 0;
}