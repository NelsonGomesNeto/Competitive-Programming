#include <stdio.h>
#include <string.h>

int main()
{
  int convidados, repeat, check, letra; char aux[99];
  while (scanf("%d", &convidados) && convidados != 0)
  {
    char nome[convidados][99];
    for (repeat = 0; repeat < convidados; repeat ++)
    {
      getchar();
      scanf("%[^\n]", nome[repeat]);
    }
    for (repeat = 0; repeat < convidados; repeat ++)
    {
      for (check = 0; check < convidados; check ++)
      {
        if (strcmp(nome[repeat],nome[check]) < 0)
        {
          strcpy(aux,nome[repeat]);
          strcpy(nome[repeat],nome[check]);
          strcpy(nome[check],aux);
        }
      }
    }
    for (repeat = 0; repeat < convidados; repeat ++)
    {
      printf("%s\n", nome[repeat]);
    }
  }
  return(0);
}
