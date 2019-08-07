#include <bits/stdc++.h>
#define lli long long int

lli fastExpRec(lli x, lli y)
{
  if (!y) return(1);
  lli ret = fastExpRec(x, y >> 1);
  ret *= ret; if (y & 1) ret *= x;
  return(ret);
}

lli fastExpBottomUp(lli x, lli y)
{
  lli ans = 1;
  while (y)
  {
    if (y & 1) ans *= x;
    x *= x, y >>= 1;
  }
  return(ans);
}

lli fastExp(lli x, lli y)
{
  return(fastExpBottomUp(x, y));
  // return(fastExpRec(x, y));
}

int main()
{
  lli x, y;
  while (scanf("%lld %lld", &x, &y) != EOF)
  {
    printf("%lld\n", fastExp(x, y));
  }
  return(0);
}
