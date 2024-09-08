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
    int n, d; scanf("%d %d", &n, &d);
    int a[n];
    for (int i = 0; i < n; i++)
      scanf("%d", &a[i]);
    sort(a, a+n);

    bool can = true;
    for (int i = 0; i < n; i++)
      if (a[i] > d)
      {
        if (i >= 2 && a[0] + a[1] <= d)
          ;
        else
          can = false;
      }
    printf("%s\n", can ? "YES" : "NO");
  }
  return 0;
}
