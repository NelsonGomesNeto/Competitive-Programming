#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

/* Tutorial:
  Notice that if you substitute d by d % m, nothing changes. Do it :3

  We want to count a_i mod m < a_(i+1) mod m
  But it's actually easier to count when that doens't happen!

  a_i mod m == a_(i+1) mod m:
    Only happens when d mod m == 0
  a_i mod m > a_(i+1) mod m:
    a_i / m < a_(i+1) / m, by EXACTLY 1 (since we did substitute d by d % m)

  Now ans = n - 1 - x - y
  x = (sumOfTheSequence / m), the amount of a_i mod m > a_(i+1) mod m
  y = how many d mod m = 0 happened in the sequence

  BUT, it's much easier if you merge both cases by instead of adding d % m;
  you add (d % m == 0 ? m : d % m). This way, all cases where d % m == 0
  will be counted as a_i mod m > a_(i+1) mod m. FANTASTIC
*/

const int maxK = 5000; int k, q;
lli d[maxK], n, x, m;
lli acc[maxK + 1];

int main()
{
  while (scanf("%d %d", &k, &q) != EOF)
  {
    for (int i = 0; i < k; i ++)
      scanf("%lld", &d[i]);

    while (q --)
    {
      scanf("%lld %lld %lld", &n, &x, &m);

      for (int i = 0; i < k; i++)
        acc[i + 1] = acc[i] + (d[i] % m == 0 ? m : d[i] % m);
      lli s = (x % m) + acc[k]*((n - 1) / k) + acc[(n - 1) % k];
      lli ans = n - 1 - s / m;
      printf("%lld\n", ans);
    }
  }
  return 0;
}