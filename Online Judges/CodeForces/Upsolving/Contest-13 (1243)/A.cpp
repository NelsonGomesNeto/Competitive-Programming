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
    lli n; scanf("%lld", &n);
    lli i, p;
    for (i = 3, p = 2; ; i += p)
    {
      if (n % i == 0)
        break;
      p *= 2;
    }
    printf("%lld\n", n / i);
  }
  return 0;
}
