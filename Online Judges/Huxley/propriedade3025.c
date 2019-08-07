#include <stdio.h>

int main()
{
  int num = 1001, numcm, numdu, teste3025;
  while ((num >= 1000) && (num <= 9999))
  {
    scanf("%i", &num);
    if ((num < 1000) || (num > 9999))
    {
      break;
    }
    numcm = num / 100;
    numdu = num % 100;
    teste3025 = (numcm + numdu) * (numcm + numdu);
    if (teste3025 == num)
    {
      printf("propriedade do 3025!\n");
    }
    else
    {
      printf("numero comum\n");
    }
  }
  return(0);
}
