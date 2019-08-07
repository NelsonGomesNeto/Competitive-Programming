#include <stdio.h>

int main()
{
  int tam; scanf("%d", &tam);
  int num[tam], ler, check, posi, start, count = 0, aux = 0;
  for (ler = 0; ler < tam; ler ++)
  {
    scanf("%d", &num[ler]);
  }
  for (ler = 0; ler < tam; ler ++)
  {
    start = num[ler];
    count = 1; check = 0;
    for (posi = ler; check < tam; posi ++, check ++)
    {
      posi = posi % tam;
      //printf("%d~%d~%d\n", start, num[posi], count);
      if (start < num[posi])
      {
        count ++;
      }
      else
      {
        count = 1;
      }
      if (count > aux)
      {
        aux = count;
      }
      start = num[posi];
    }
  }
  printf("%d\n", aux);
  return(0);
}
