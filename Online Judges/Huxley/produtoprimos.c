#include <stdio.h>

int main()
{
  int n[4], check = 3, divi, teste = 0, produto, saoprimos = 0;
  scanf("%i %i %i %i", &n[0], &n[1], &n[2], &n[3]);
  divi = n[check] + 1;
  while (check != -1)
  {
    if (!(divi == 0))
    {
      divi --;
    }
    if (divi == 0)
    {
      check --;
      if (check == -1)
      {
        break;
      }
      divi = n[check];
      teste = 0;
    }
    if (n[check] % divi == 0)
    {
      teste += divi;
    }
    if (teste == n[check] + 1 && divi == 1)
    {
      saoprimos ++;
    }
  }
  if (saoprimos == 4)
  {
    produto = (n[0] * n[1] * n[2] * n[3]);
    printf("%i\n", produto);
  }
  else
  {
    printf("SEM PRODUTO\n");
  }
  return(0);
}
