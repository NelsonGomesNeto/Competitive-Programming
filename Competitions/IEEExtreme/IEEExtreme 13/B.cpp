#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

lli n, a, b, k, lf, done;

lli binarySearch()
{
  lli lo = a, hi = b;
  while (lo < hi)
  {
    lli mid = (lo + hi) >> 1LL;
    lli after = lf - mid;
    if ((after / b + (after % b != 0)) + done + 1 <= k) hi = mid;
    else lo = mid + 1;
  }
  return lo;
}

int main()
{
  while (scanf("%lld %lld %lld", &n, &a, &b) != EOF)
  {
    if (n < a) printf("NO\n");
    else if (n >= a && n <= b) printf("YES\n%lld\n", n);
    else
    {
      k = n / b + (n % b != 0);
      if (k > 100000) printf("NO\n");
      else
      {
        vector<lli> ans(k);
        lf = n, done = 0;
        for (int i = 0; i < k; i ++, done ++)
        {
          ans[i] = binarySearch();
          lf -= ans[i];
          DEBUG printf("\t%lld\n", lf);
        }
        if (lf == 0)
        {
          printf("YES\n");
          for (int i = 0; i < k; i ++)
            printf("%lld%c", ans[i], i < k - 1 ? ' ' : '\n');
        }
        else
        {
          printf("NO\n");
        }
      }
    }
  }
  return 0;
}
