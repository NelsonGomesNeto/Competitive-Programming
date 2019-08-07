#include <stdio.h>
#include <string.h>

int main()
{
  int testes, ordem, repeat, faz; scanf("%d", &testes);
  for (faz = 0; faz < testes; faz ++)
  {
    char num[999999], aux;
    getchar();
    scanf("%s", num);
    for (repeat = 0; repeat < strlen(num); repeat ++)
    {
      for (ordem = repeat; ordem < strlen(num); ordem ++)
      {
        if (num[repeat] < num[ordem])
        {
          aux = num[repeat];
          num[repeat] = num[ordem];
          num[ordem] = aux;
        }
      }
    }
    printf("Caso %d: %s\n", faz + 1, num);
  }
  return(0);
}
