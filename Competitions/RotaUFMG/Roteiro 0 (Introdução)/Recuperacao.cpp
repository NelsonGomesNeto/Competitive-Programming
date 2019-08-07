#include <bits/stdc++.h>

int main()
{
  int n, t = 0;
  while (scanf("%d", &n) != EOF)
  {
    if (t) printf("\n");

    int sum = 0, num, toPrint = -1e7;
    while (n -- > 0)
    {
      scanf("%d", &num);
      if (num == sum && toPrint == -1e7)
        toPrint = num;
      sum += num;
    }

    printf("Instancia %d\n", ++ t);
    if (toPrint == -1e7)
      printf("nao achei\n");
    else
      printf("%d\n", toPrint);
  }
  return(0);
}