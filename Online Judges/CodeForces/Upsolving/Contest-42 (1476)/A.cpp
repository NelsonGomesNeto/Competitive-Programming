#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

int main()
{
  int t; scanf("%d", &t);
  for (int tt = 1; tt <= t; tt++)
  {
    int n; lli k; scanf("%d %lld", &n, &k);
    lli target = k * (n / k + (n % k != 0));
    lli ans = target / n + (target % n != 0);
    printf("%lld\n", ans);
  }
  return 0;
}
