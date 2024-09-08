#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

int main()
{
  int n;
  while (~scanf("%d", &n))
  {
    lli a[n], b[n], c[n];
    for (int i = 0; i < n; i++)
      scanf("%lld", &a[i]);
    for (int i = 0; i < n; i++)
      scanf("%lld", &b[i]);

    lli aa = a[0], bb = b[0];
    for (int i = 0; i < n; i++)
    {
      aa = max(aa, a[i]);
      bb = b[i];
      c[i] = aa * bb;
      if (i)
        c[i] = max(c[i], c[i - 1]);
    }

    for (int i = 0; i < n; i++)
      printf("%lld%c", c[i], '\n');
  }
  return 0;
}