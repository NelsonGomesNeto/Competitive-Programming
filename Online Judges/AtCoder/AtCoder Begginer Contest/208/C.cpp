#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 2e5; int n; lli k;
pair<lli, int> a[maxN];
lli ans[maxN];

int main()
{
  while (~scanf("%d %lld", &n, &k))
  {
    for (int i = 0; i < n; i++)
    {
      scanf("%lld", &a[i].first);
      a[i].second = i;
    }
    sort(a, a+n);

    for (int i = 0; i < n; i++)
      ans[i] = k / n;

    for (int i = 0, end = k % n; i < end; i++)
      ans[a[i].second]++;

    for (int i = 0; i < n; i++)
      printf("%lld\n", ans[i]);
  }
  return 0;
}