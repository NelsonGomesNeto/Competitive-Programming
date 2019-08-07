#include <stdio.h>

int main()
{
  int num, ler, divi = 1, raz; scanf("%d", &num);
  int sequencia[num];
  for (ler = 0; ler < num; ler ++)
  {
    scanf("%d", &sequencia[ler]);
  }
  for (ler = 0; ler < num - 1; ler ++)
  {
    if (ler == 0)
    {
      raz = sequencia[ler + 1] - sequencia[ler];
    }
    else
    {
      if (sequencia[ler + 1] - sequencia[ler] != raz)
      {
        raz = sequencia[ler + 2] - sequencia[ler + 1];
        divi ++;
      }
    }
    //printf("%d\n", raz);
  }
  printf("%d\n", divi);
  return(0);
}
