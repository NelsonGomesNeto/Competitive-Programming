#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

lli h;

lli solve(lli hh)
{
  if (hh <= 1) return hh;
  return 1LL + 2LL*solve(hh >> 1LL);
}

int main()
{
  // for (h = 1; h < 10; h ++)
  //   printf("%lld %lld\n", h, solve(h));
  while (scanf("%lld", &h) != EOF)
    printf("%lld\n", solve(h));

  return 0;
}