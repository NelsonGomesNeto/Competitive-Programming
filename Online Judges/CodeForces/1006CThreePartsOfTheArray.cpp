#include <bits/stdc++.h>
using namespace std;
#define lli long long int

int main()
{
  int n; scanf("%d", &n);
  int a[n]; lli s[n + 1]; s[0] = 0;
  for (int i = 0; i < n; i ++)
  {
    scanf("%d", &a[i]);
    s[i + 1] = s[i] + a[i];
  }

  lli ans = 0;
  int lo = 1, hi = n - 1;
  if (n > 1 && s[lo] == s[n] - s[hi]) ans = s[lo];
  while (lo < hi)
  {
    while (lo < hi && s[lo] > (s[n] - s[hi])) hi --;
    while (lo < hi && s[lo] < (s[n] - s[hi])) lo ++;
    if (s[lo] == s[n] - s[hi]) ans = max(ans, s[lo ++]);
  }
  printf("%lld\n", ans);

  return(0);
}
