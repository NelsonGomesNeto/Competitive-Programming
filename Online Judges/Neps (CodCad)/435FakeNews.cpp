#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 100;
int a[maxN], n, k;

int got(int pos)
{
  int ans = 0;
  for (int i = 0; i < n; i ++)
    ans += abs(a[i] - pos) <= k;
  return ans;
}

int main()
{
  int q; scanf("%d", &q);
  while (q --)
  {
    scanf("%d %d", &n, &k);
    for (int i = 0; i < n; i ++) scanf("%d", &a[i]);
    sort(a, a+n);
    int ans = a[0];
    for (int i = a[0] + 1; i <= a[n - 1]; i ++)
      if (got(i) > got(ans))
        ans = i;
    printf("%d\n", ans);
  }
  return 0;
}