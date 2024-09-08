#include <stdio.h>
#include <string.h>

int main()
{
  char num[999999]; scanf("%[^\n]", num);
  int ler, number = 0, teve = 0;
  for (ler = 0; ler < strlen(num); ler ++)
  {
    if (toupper(num[ler]) == 'I' && toupper(num[ler + 1]) == 'V')
    {
      number = 4;
      ler ++;
    }
    else if (toupper(num[ler]) == 'I')
    {
      number ++;
    }
    else if (toupper(num[ler]) == 'V')
    {
      number = 5;
    }
    teve ++;
  }
  //printf("%d\n", number);
  if (teve == 0)
  {
    number = 1;
  }
  if (number % 5 != 0)
  {
    printf("O resto pela divisao por 5 do numero dado e igual a %d!\n", number % 5);
  }
  else
  {
    printf("O numero e multiplo de 5!\n");
  }
  return(0);
}//O resto pela divisao por 5 do numero dado e igual a 1!
