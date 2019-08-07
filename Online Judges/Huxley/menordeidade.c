#include <stdio.h>

int main()
{
  int idade;
  scanf("%i", &idade);
  if (idade >= 18)
  {
    printf("maior de idade\n");
  }
  if (idade < 18)
  {
    printf("menor de idade\n");
  }
  if (idade % 2 == 0)
  {
    printf("par || dobro: %i || meteade: %i\n", (idade * 2), (idade / 2));
  }
  if (idade % 2 != 0)
  {
    printf("impar\n");
  }
  return(0);
}
