#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int

int main()
{
  char number[100]; scanf("%s", number);
  int moves = 100, size = strlen(number);
  int combinations = pow(2, size);
  for (int k = 0; k < combinations; k ++)
  {
    lli now = 0, j = 0, m = 0, i = k, can = 1;
    while (i)
    {
      if (now == 0 && (number[j]-'0') == 0 && !(i & 1)) can = 0;
      now = (now * (!(i & 1) ? 10 : 1)) + ((number[j]-'0') * (!(i & 1) == 1));
      m += !(i & 1) == 1;
      i /= 2; j ++;
    }
    while (j < size)
    {
      if (now == 0 && (number[j]-'0' == 0)) can = 0;
      now = (now * 10) + (number[j]-'0'); j ++; m ++;
    }
    lli sq = sqrt(now);
    DEBUG printf("%lld %lld %lld\n", now, size - m, can);
    if ((sq*sq == now) && now && ((size - m) < moves) && can) moves = size - m;
  }

  printf("%d\n", moves == 100 ? -1 : moves);

  return(0);
}
