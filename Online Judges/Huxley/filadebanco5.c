#include <stdio.h>

int main()
{
  int primeira, segunda, comer;
  scanf("%d %d %d", &primeira, &segunda, &comer);
  //printf("%d ~ %d\n", primeira, segunda);
  int ler, filaP[primeira], filaS[segunda];
  for (ler = 0; ler < primeira; ler ++)
  {
    scanf("%d", &filaP[ler]);
  }
  for (ler = 0; ler < segunda; ler ++)
  {
    scanf("%d", &filaS[ler]);
  }
  int i1, i2;
  if (comer == 1)
  {
    for (ler = 0, i1 = 0, i2 = 0; ler < primeira + segunda;)
    {
      if (ler % 2 != 0 && i1 < primeira)
      {
        printf("%d\n", filaP[i1]);
        i1 ++; ler ++;
      }
      else if (i2 < segunda)
      {
        printf("%d\n", filaS[i2]);
        i2 ++; ler ++;
      }
      else
      {
        printf("%d\n", filaP[i1]);
        i1 ++; ler ++;
      }
    }
  }
  else
  {
    for (ler = 0, i1 = 0, i2 = 0; ler < primeira + segunda;)
    {
      if (ler % 2 == 0 && i1 < primeira)
      {
        printf("%d\n", filaP[i1]);
        i1 ++; ler ++;
      }
      else if (i2 < segunda)
      {
        printf("%d\n", filaS[i2]);
        i2 ++; ler ++;
      }
      else
      {
        printf("%d\n", filaP[i1]);
        i1 ++; ler ++;
      }
    }
  }
  return(0);
}
