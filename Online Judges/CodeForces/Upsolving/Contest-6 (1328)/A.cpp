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
    lli a, b; scanf("%lld %lld", &a, &b);
    if (a % b == 0)
      printf("0\n");
    else
    {
      lli ans = a / b + (a % b != 0);
      printf("%lld\n", ans*b - a);
    }
  }
  return 0;
}
