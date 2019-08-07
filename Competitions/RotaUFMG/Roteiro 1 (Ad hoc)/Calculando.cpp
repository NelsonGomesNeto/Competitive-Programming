#include <bits/stdc++.h>

int main()
{
  int n, t = 0;
  while (scanf("%d", &n) && n)
  {
    if (t) printf("\n");

    int sum = 0, x; char oper = '+';
    for (int i = 0; i < n; i ++)
    {
      if (i) scanf("%c", &oper);
      scanf("%d", &x);
      sum += oper == '+' ? x : -x;
    }
    
    printf("Teste %d\n%d\n", ++ t, sum);
  }
  return(0);
}