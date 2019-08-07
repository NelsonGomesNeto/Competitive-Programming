#include <bits/stdc++.h>
int h1, a1, c, h2, a2;

int main()
{
  scanf("%d %d %d %d %d", &h1, &a1, &c, &h2, &a2);

  int strike = h2 / a1 + (h2 % a1 > 0), hurt = h1 / a2 + (h1 % a2 > 0), movements = h2 / a1 + (h2 % a1 > 0);
  //printf("%d %d\n", strike, hurt);
  if (strike > hurt)
  {
    while (strike > hurt)
    {
      h1 += (c - a2);
      hurt = h1 / a2 + (h1 % a2 > 0);
      movements ++;
    }
    printf("%d\n", movements);
    for (int i = 0; i < movements - strike; i ++)
      printf("HEAL\n");
  }
  else
    printf("%d\n", movements);
  for (int i = 0; i < strike; i ++)
    printf("STRIKE\n");

  return(0);
}