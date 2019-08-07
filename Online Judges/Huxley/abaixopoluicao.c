#include <stdio.h>

int main()
{
  int ncarros = 0, multa = 0; float total = 0;
  while (ncarros != 999)
  {
    if (ncarros > 2)
    {
      multa ++;
      total += (ncarros - 2) * 12.89;
    }
    scanf("%i", &ncarros);
  }
  printf("%.2f\n%i\n", total, multa);
  return(0);
}
