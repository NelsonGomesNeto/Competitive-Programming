#include <stdio.h>

int main()
{
  int testes; scanf("%d", &testes);
  int K, A, B, C, D, x, y, total = 1;
  while (testes > 0)
  {
    scanf("%d %d %d %d %d", &K, &A, &B, &C, &D);
    x = B;
    while ((B - A) + (D - C) > K)
    {
      total *= (B - A) + (D - C);
      if (B > A)
      {
        B --;
      }
      else if (D > C)
      {
        D --;
      }
    }
    /*while (x >= A)
    {
      y = D;
      while (y >= C)
      {
        if (x + y > K)
        {
          total ++;
        }
        else { y = C - 1; }
        y --;
      }
      if (x + D <= K)
      {
        x = A - 1;
      }
      x --;
    }*/
    printf("%d\n", total);
    testes --;
  }
  return(0);
}
