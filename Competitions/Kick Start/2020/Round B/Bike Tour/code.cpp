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
    int h[n]; for (int i = 0; i < n; i++) scanf("%d", &h[i]);
    int ans = 0;
    for (int i = 1; i < n - 1; i++)
      if (h[i] > h[i - 1] && h[i] > h[i + 1])
        ans++;
    printf("Case #%d: %d\n", tt, ans);
  }
  return 0;
}