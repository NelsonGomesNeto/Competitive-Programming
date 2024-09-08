#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

int main()
{
  lli n;
  while (~scanf("%lld", &n))
  {
    lli i = 0, p = 1;
    while (2*p <= n)
    {
      p *= 2, i++;
    }
    printf("%lld\n", i);
  }
  return 0;
}