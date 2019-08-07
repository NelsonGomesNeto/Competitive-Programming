#include <stdio.h>
#include <math.h>

int main()
{
  int A, B, C, D;
  scanf("%d %d %d %d", &A, &B, &C, &D);
  int sqrtC = sqrt(C), i, j;
  int end = sqrtC * 2, divisores[end], big[end], final[end];
  for (i = 0; i < end; i ++)
  {
    divisores[i] = 1000000001;
    big[i] = 1000000001;
  }

  for (i = 1, j = 0; i <= sqrtC; i ++)
    if (C % i == 0)
    {
      big[j] = C / i;
      divisores[j ++] = i;
    }

  end = j; int o = 0, b = 0, aux;
  for (o = 0; o < end; o ++)
    for (b = o + 1; b < end; b ++)
      if (big[b] < big[o])
      {
        aux = big[o];
        big[o] = big[b];
        big[b] = aux;
      }

  o = b = 0;
  for (i = 0; o < end || b < end; i ++)
  {
    if (divisores[o] < big[b])
      final[i] = divisores[o ++];
    else
      final[i] = big[b ++];
  }

  i = 0;
  do
  {
    if (final[i] % A == 0 && final[i] % B != 0 /*&& C % divisores[i] == 0*/ && D % final[i] != 0)
    {
      printf("%d\n", final[i]); return(0);
    }
    i ++;
  } while (i <= end * 2);
  printf("-1\n");

  return(0);
}
