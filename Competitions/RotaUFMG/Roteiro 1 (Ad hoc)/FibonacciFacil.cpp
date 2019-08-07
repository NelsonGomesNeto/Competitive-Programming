#include <bits/stdc++.h>

int main()
{
  int n; scanf("%d", &n);

  int a = 0, b = 1, aux;
  for (int i = 0; i < n; i ++)
  {
    printf("%d%c", a, i < n - 1 ? ' ' : '\n');
    aux = a;
    a = a + b;
    b = aux;
  }

  return(0);
}