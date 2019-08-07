#include <bits/stdc++.h>
#define lli long long int

int main()
{
  int n, m; scanf("%d %d", &n, &m);
  int a[m]; for (int i = 0; i < m; i ++) scanf("%d", &a[i]);

  lli minTime = 0; int at = 1;
  for (int i = 0; i < m; i ++)
  {
    if (a[i] == at) continue;
    if (at > a[i]) minTime += (n - at) + a[i];
    else minTime += a[i] - at;
    at = a[i];
  }

  printf("%lld\n", minTime);
  return(0);
}