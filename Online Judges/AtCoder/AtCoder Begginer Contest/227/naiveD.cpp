#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

/*
n!
/ (k! * (n - k)!)
*/

const int maxN = 2e5; int n, k;
lli a[maxN];

int main()
{
  while (~scanf("%d %d", &n, &k))
  {
    for (int i = 0; i < n; i++)
      scanf("%lld", &a[i]);
    sort(a, a+n);
    reverse(a, a+n);

    lli ans = 0;
    while (a[k - 1] > 0)
    {
      ans++;
      for (int i = 0; i < k; i++)
        a[i]--;

      sort(a, a+n);
      reverse(a, a+n);

      printf("\t");
      for (int i = 0; i < n; i++)
        printf("%lld%c", a[i], i < n - 1 ? ' ' : '\n');
    }
    printf("%lld\n", ans);
  }
  return 0;
}