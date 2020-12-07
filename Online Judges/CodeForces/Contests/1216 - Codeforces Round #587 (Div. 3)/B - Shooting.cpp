#include <bits/stdc++.h>
#define lli long long int
using namespace std;

int main()
{
  int n;
  while (scanf("%d", &n) != EOF)
  {
    pair<lli, int> a[n]; for (int i = 0; i < n; i ++) { scanf("%lld", &a[i].first); a[i].second = i; }
    sort(a, a+n); reverse(a, a+n);
    lli ans = 0;
    for (int i = 0; i < n; i ++)
      ans += a[i].first * i + 1;
    printf("%lld\n", ans);
    for (int i = 0; i < n; i ++)
      printf("%d%c", a[i].second + 1, i < n - 1 ? ' ' : '\n');
  }
  return(0);
}
