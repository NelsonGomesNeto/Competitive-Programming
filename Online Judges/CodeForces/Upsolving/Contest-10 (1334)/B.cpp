#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 1e5; int n; lli x;
lli a[maxN];

bool can(int m)
{
  lli sum = 0;
  for (int i = 0; i < m; i++) sum += a[i];
  return sum / x >= m;
}

int main()
{
  int t; scanf("%d", &t);
  while (t--)
  {
    scanf("%d %lld", &n, &x);
    for (int i = 0; i < n; i++) scanf("%lld", &a[i]);
    sort(a, a+n, greater<lli>());

    int lo = 0, hi = n;
    while (lo < hi)
    {
      int mid = (lo + hi + 1) >> 1;
      if (can(mid)) lo = mid;
      else hi = mid - 1;
    }
    printf("%d\n", lo);
  }
  return 0;
}
