#include <bits/stdc++.h>

int main()
{
  int a, b; scanf("%d %d", &a, &b);
  int total = 0;
  while (a >= b)
  {
    total += a - a % b;
    a = a / b + a % b;
  }
  total += a;
  printf("%d\n", total);

  return(0);
}