#include <bits/stdc++.h>

int main()
{
  int overflow; scanf("%d", &overflow);
  int a, b, res; char oper;
  scanf("%d %c %d", &a, &oper, &b);
  if (oper == '+')
    res = a + b;
  else
    res = a * b;

  if (res <= overflow)
    printf("OK\n");
  else
    printf("OVERFLOW\n");

  return(0);
}