#include <stdio.h>
#include <string.h>

int main()
{
  int pessoas, DNA;
  while (scanf("%d %d", &pessoas, &DNA) && !(pessoas == 0 && DNA == 0))
  {
    int ler, check, igual, clones[pessoas + 10]; char existencia[pessoas][DNA + 10];
    for (ler = 0; ler < pessoas; ler ++)
    {
      getchar();
      scanf("%[^\n]", existencia[ler]);
      clones[ler] = 0;
    }
    for (ler = 0; ler < pessoas; ler ++)
    {
      for (check = 0, igual = 0; check < pessoas; check ++)
      {
        if (strcmp(existencia[ler], existencia[check]) == 0 && check != ler && existencia[ler][0] != '.')
        {
          existencia[check][0] = '.';
          igual ++;
        }
      }
      if (existencia[ler][0] != '.')
      {
        clones[igual] ++;
      }
    }
    for (ler = 0; ler < pessoas; ler ++)
    {
      printf("%d\n", clones[ler]);
    }
  }
  return(0);
}
