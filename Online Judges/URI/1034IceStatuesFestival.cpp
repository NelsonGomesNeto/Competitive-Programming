#include <bits/stdc++.h>
#define lli long long int
using namespace std;

const int maxM = 1e6;
int ans[maxM + 1];

int main()
{
  int t; scanf("%d", &t);
  while (t --)
  {
    int n, m; scanf("%d %d", &n, &m);
    int a[n]; for (int i = 0; i < n; i ++) scanf("%d", &a[i]);
    sort(a, a+n);

    ans[1] = 1;
    for (int i = 2; i <= m; i ++)
    {
      ans[i] = m;
      for (int j = 0; j < n && a[j] <= i; j ++)
        ans[i] = min(ans[i], 1 + ans[i - a[j]]);
    }
    printf("%d\n", ans[m]);
  }
  return(0);
}