#include <stdio.h>

int main()
{
  int Rei, Hel; int ReiW = 0, HelW = 0;
  int ReiSoma = 0, HelSoma = 0, repeat;
  for (repeat = 0; repeat < 5; repeat ++)
  {
    scanf("%i\n%i", &Rei, &Hel);
    ReiSoma += Rei; HelSoma += Hel;
    if (Rei > Hel) { ReiW ++; }
    else if (Hel > Rei) { HelW ++; }
  }
  if (ReiW > HelW)
  {
    printf("REINALDO\n");
  }
  else if (HelW > ReiW)
  {
    printf("HELENA\n");
  }
  else
  {
    if (ReiSoma > HelSoma)
    {
      printf("REINALDO\n");
    }
    else if (HelSoma > ReiSoma)
    {
      printf("HELENA\n");
    }
    else
    {
      printf("EMPATE\n");
    }
  }
  return(0);
}
