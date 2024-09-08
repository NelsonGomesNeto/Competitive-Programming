#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 1e5; int n; lli x;
lli a[maxN];

int main()
{
  int t; scanf("%d", &t);
  for (int tt = 1; tt <= t; tt++)
  {
    scanf("%d %lld", &n, &x);
    for (int i = 0; i < n; i++)
      scanf("%lld", &a[i]);

    lli sum = 0;
    for (int i = 0; i < n; i++)
      sum += a[i];

    lli c = 0, b = sum / x + (sum % x != 0);
    for (int i = 0; i < n; i++)
      c += a[i] / x + (a[i] % x != 0);
    printf("%lld %lld\n", b, c);
  }
  return 0;
}
