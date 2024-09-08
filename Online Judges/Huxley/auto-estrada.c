#include <stdio.h>

int main()
{
  int C, check, painel = 0;
  scanf("%i", &C); check = C;
  char tipo[C];
  scanf("%s", tipo);
  for (check = 0; check < C; check ++)
  {
    if (tipo[check] == 'P' || tipo[check] == 'C')
    {
      painel += 2;
    }
    else if (tipo[check] == 'A')
    {
      painel ++;
    }
  }
  printf("%i\n", painel);
  return(0);
}
