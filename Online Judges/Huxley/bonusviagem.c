#include <stdio.h>

int main()
{
  int bonus;
  scanf("%i", &bonus);
  if (bonus < 3000)
  {
    printf("ARGENTINA\n");
  }
  else if (bonus >= 3000 && bonus <= 4000)
  {
    printf("ESPANHA\n");
  }
  else if (bonus > 4000)
  {
    printf("ALEMANHA\n");
  }
  return(0);
}
