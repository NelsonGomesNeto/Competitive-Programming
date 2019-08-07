#include <bits/stdc++.h>

int main()
{
  int plays, t = 0;
  while (scanf("%d", &plays) && plays)
  {
    if (t) printf("\n");

    char a[100], b[100];
    scanf("\n%s\n%s", a, b);

    printf("Teste %d\n", ++ t);
    while (plays -- > 0)
    {
      int ah, bh; scanf("%d %d", &ah, &bh);
      printf("%s\n", (ah + bh) & 1 ? b : a);
    }
  }
  
  return(0);
}