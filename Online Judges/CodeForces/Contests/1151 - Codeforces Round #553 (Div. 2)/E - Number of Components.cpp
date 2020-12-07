#include <bits/stdc++.h>
#define lli long long int
using namespace std;

const int maxN = 1e5; int n;
lli a[maxN + 1];

int main()
{
  scanf("%d", &n);
  for (int i = 1; i <= n; i ++) scanf("%lld", &a[i]);

  lli ans = 0;
  a[0] = 0;
  for (int i = 1; i <= n; i ++)
  {
    if (a[i] > a[i - 1])
      ans += (n - a[i] + 1) * (a[i] - a[i - 1]);
    if (a[i - 1] > a[i])
      ans += a[i] * (a[i - 1] - a[i]);
  }

  printf("%lld\n", ans);

  return(0);
}
/*
for (int i = 1; i <= n; i ++)
    for (int j = i; j <= n; j ++)
    {
      int components = 0;
      for (int k = 0; k < n; k ++)
        if (a[k] >= i && a[k] <= j)
        {
          while (k < n && a[k] >= i && a[k] <= j) k ++;
          k --, components ++;
        }
      ans += components;
    }
*/