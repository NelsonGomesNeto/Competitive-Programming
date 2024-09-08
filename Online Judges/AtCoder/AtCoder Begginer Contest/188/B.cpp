#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

int main()
{
  int n;
  while (~scanf("%d", &n))
  {
    lli a[n], b[n];
    for (int i = 0; i < n; i++)
      scanf("%lld", &a[i]);
    for (int i = 0; i < n; i++)
      scanf("%lld", &b[i]);

    lli ans = 0;
    for (int i = 0; i < n; i++)
      ans += a[i] * b[i];
    printf("%s\n", ans == 0 ? "Yes" : "No");
  }
  return 0;
}