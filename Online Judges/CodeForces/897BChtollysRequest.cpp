#include <bits/stdc++.h>
#define lli long long int

lli getZcy(lli num)
{
  lli aux = num, zcy = 0, d = 1, b;
  while (aux > 0)
  {
    d *= 10;
    aux /= 10;
  }
  aux = num; b = d; d /= 10;
  while (aux > 0)
  {
    zcy += (aux % 10) * d;
    d /= 10;
    aux /= 10;
  }
  zcy += num * b;
  return(zcy);
}

int main()
{
  lli n, m, sum = 0; scanf("%lld %lld", &n, &m);
  lli now = 1, zcy = 0;
  for (int i = 0; i < n; i ++)
  {
    zcy = getZcy(now);
    // printf("%lld\n", zcy);
    sum = (sum + zcy) % m;
    now ++;
  }

  printf("%lld\n", sum);

  return(0);
}