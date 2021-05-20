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
    int a[n]; for (int i = 0; i < n; i++) scanf("%d", &a[i]);

    int ans = 0;
    for (int i = 0; i < n; i++)
      if (a[i] != i + 1)
      {
        ans++;
        break;
      }

    if (ans)
      ans += !(a[0] == 1 || a[n - 1] == n);

    if (ans)
      ans += a[0] == n && a[n - 1] == 1;

    printf("%d\n", ans);
  }
  return 0;
}
