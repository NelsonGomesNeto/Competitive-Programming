#include <stdio.h>
#define lli long long int

lli pot(lli x, lli expo)
{
  lli res;
  if (expo == 0)
  {
    return(1);
  }
  res = pot(x, expo / 2);
  if (expo % 2 != 0)
  {
    return (x * res * res);
  }
  return (res * res);
}

int main()
{
  lli base, expoente; scanf("%lld %lld", &base, &expoente);
  printf("%lld\n", pot(base, expoente));
  return(0);
}
