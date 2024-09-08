#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

int main()
{
  lli a;
  char b[5];
  while (scanf("%lld %s", &a, b) != EOF)
  {
    for (int i = 0; i < 4; i++) b[i] -= '0';
    lli bb = (int)b[0] * 100 + (int)b[2] * 10 + (int)b[3];
    lli ans = a * bb / 100;

    printf("%lld\n", ans);
  }
  return 0;
}