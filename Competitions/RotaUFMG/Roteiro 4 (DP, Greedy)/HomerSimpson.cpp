#include <bits/stdc++.h>

int main()
{
  int m, n, t;
  while (scanf("%d %d %d", &m, &n, &t) != EOF)
  {
    if (m > n)
    {
      int aux = m; m = n; n = aux;
    }
    int h = t / m, bh = t / m, bt = (m * (t / m)), at = (m * (t / m));
    while (at >= 0)
    {
      int newT = n * ((t - at) / n), newH = (t - at) / n;
      //printf("%d %d %d %d %d\n", at, newT, t - newT - at, newH, h);
      if (newT + at > bt || (newT + at == bt && newH + h > bh))
      {
        bt = newT + at;
        bh = newH + h;
      }
      at -= m;
      h --;
    }

    printf("%d", bh);
    if (t - bt)
      printf(" %d", t - bt);
    printf("\n");
  }
  return(0);
}