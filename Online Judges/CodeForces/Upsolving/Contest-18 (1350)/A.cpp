#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

int main()
{
  int t; scanf("%d", &t);
  while (t--)
  {
    int n; lli k; scanf("%d %lld", &n, &k);
    lli ans = n;
    while ((ans & 1LL) && k)
    {
      bool done = false;
      for (int i = 2, end = sqrt(ans); i <= ans; i++)
        if (ans % i == 0)
        {
          ans += i;
          done = true;
          break;
        }
      if (!done) ans += ans;
      k--;
    }
    if (k && !(ans & 1LL)) ans += 2LL*k;

    printf("%lld\n", ans);
  }
  return 0;
}
