#include <stdio.h>

int dest, peso, expres, Km, truck = 0, dias = 0;
int totalTruck = 0, preco = 0, diasMais = 0;

int main()
{
  scanf("%i", &dest);
  while (dest > 0)
  {
    scanf("%i\n%i\n%i", &peso, &expres, &Km);
    if (expres == 0)
    {
      if (peso % 10 == 0)
      {
        truck += peso / 10;
      }
      else
      {
        truck += (peso / 10) + 1;
      }

      preco += (500 * truck);

      if (Km % 100 == 0)
      {
        dias += Km / 100;
      }
      else
      {
        dias += (Km / 100) + 1;
      }
    }
    else
    {
      if (peso % 5 == 0)
      {
        truck += peso / 5;
      }
      else
      {
        truck += (peso / 5) + 1;
      }

      preco += (1200 * truck);

      if (Km % 250 == 0)
      {
        dias += Km / 250;
      }
      else
      {
        dias += (Km / 250) + 1;
      }
    }
    if (diasMais < dias)
    {
      diasMais = dias;
    }
    totalTruck += truck; truck = 0; dias = 0;
    dest --;
  }
  printf("%i %i %i\n", totalTruck, preco, diasMais);
}
