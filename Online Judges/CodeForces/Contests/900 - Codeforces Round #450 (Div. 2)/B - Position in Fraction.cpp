#include <bits/stdc++.h>

int main()
{
  int a, b, c; scanf("%d %d %d", &a, &b, &c);

  int first = -1;
  for (int i = 1; i <= 1e6; i ++)
  {
    a *= 10;
    int divisor = a / b;
    if (divisor == c)
    {
      first = i; break;
    }
    a -= b * divisor;
  }

  printf("%d\n", first);

  return(0);
}