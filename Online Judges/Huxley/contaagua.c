#include <stdio.h>

int main()
{
  int consumo, conta = 0;
  scanf("%i", &consumo);
  if (consumo <= 10)
  {
    conta += 7;
  }
  else if (consumo > 10 && consumo <= 30)
  {
    conta += 7 + (consumo - 10);
  }
  else if (consumo > 30 && consumo <= 100)
  {
    conta += 7 + 20 + ((consumo - 30) * 2);
  }
  else if (consumo > 100)
  {
    conta += 7 + 20 + 140 + ((consumo - 100) * 5);
  }
  printf("%i\n", conta);
  return(0);
}
