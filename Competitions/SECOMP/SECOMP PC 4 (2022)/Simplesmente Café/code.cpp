#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 1e5;
int n;
int a[maxN];
int even, odd;

int main()
{
  while (~scanf("%d", &n))
  {
    even = odd = 0;
    for (int i = 0; i < n; ++i)
    {
      scanf("%d", &a[i]);
      even += ~a[i] & 1;
      odd += a[i] & 1;
    }

    lli o = 0, e = 0;
    lli ans2 = 0;
    for (int i = 0; i < n; ++i)
    {
      if (a[i] & 1) ++o, ans2 += e;
      else ++e, ans2 += o;
    }

    lli ans = ((lli)even * odd);
    assert(ans == ans2);
    printf("%lld\n", ans);
  }
  return 0;
}
