#include <stdio.h>

int main()
{
  int reg; scanf("%d", &reg);
  if (reg < 2)
  {
    printf("Nordeste\n");
  }
  else if (reg < 3)
  {
    printf("Norte\n");
  }
  else if (reg < 5)
  {
    printf("Centro-Oeste\n");
  }
  else if (reg < 10)
  {
    printf("Sul\n");
  }
  else
  {
    printf("Sudeste\n");
  }
}
