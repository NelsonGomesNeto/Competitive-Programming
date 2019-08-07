#include <bits/stdc++.h>
#define lli unsigned long long int
using namespace std;

/* Tutorial:
  Test if it's possible is simple:
    (1LL<<(n-2))*(a + 1) <= b && b <= (1LL<<(n-2))*(a + m)
    must be true for some n between 2 and 50

  To fill, we will use the previous found n and binary search for
  each r. So, binary search for the smallest r which from that point
  on, choosing m for every r will still be above or equal to b. That
  can be known through this formula: (1LL << (n - i - 2)) * (2*sum + r + m)
*/

int q, n; lli a, b, m;
lli sequence[50], sum;

bool possible(int i, lli r)
{
  lli minEnd = (1LL << (n - i - 2))*(2*sum + r + 1);
  lli maxEnd = (1LL << (n - i - 2))*(2*sum + r + m);
  return(maxEnd >= b);
}

int main()
{
  scanf("%d", &q);
  while (q --)
  {
    scanf("%lld %lld %lld", &a, &b, &m);
    bool can = false;
    for (n = 2; n <= 50 && !can; n ++)
      can = (1LL<<(n-2))*(a + 1) <= b && b <= (1LL<<(n-2))*(a + m);
    n --;

    if (a == b) printf("1 %lld\n", a);
    else if (!can) printf("-1\n");
    else
    {
      sequence[0] = sum = a; sequence[n - 1] = b;
      for (int j = 1; j < n - 1; j ++)
      {
        lli lo = 1, hi = m;
        while (lo < hi)
        {
          lli mid = ((lo + hi) >> 1);
          if (possible(j, mid)) hi = mid;
          else lo = mid + 1;
        }
        sequence[j] = sum + lo;
        sum += sequence[j];
      }
      printf("%d", n);
      for (int i = 0; i < n; i ++) printf(" %lld", sequence[i]);
      printf("\n");
    }
  }
  return(0);
}
