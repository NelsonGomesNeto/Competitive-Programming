#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 2e5; int n;
lli a[maxN];
int l[maxN], r[maxN];

int main()
{
  while (scanf("%d", &n) != EOF)
  {
    for (int i = 0; i < n; i ++)
      scanf("%lld", &a[i]);

    l[0] = 1;
    for (int i = 1; i < n; i ++)
      l[i] = a[i] > a[i - 1] ? 1 + l[i - 1] : 1;
    r[n - 1] = 1;
    for (int i = n - 2; i >= 0; i --)
      r[i] = a[i] < a[i + 1] ? 1 + r[i + 1] : 1;

    int ans = r[0];
    for (int i = 0; i < n - 1; i ++)
      ans = max(ans, r[i + 1] + (i && a[i - 1] < a[i + 1] ? l[i - 1] : 0));
    printf("%d\n", ans);
  }
  return 0;
}
