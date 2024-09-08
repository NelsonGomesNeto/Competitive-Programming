#include <stdio.h>

int main()
{
  int numbermenor, number, repeat = 0;
  scanf("%i", &number);
  numbermenor = number;
  while (repeat < 2)
  {
    scanf("%i", &number);
    if (number <= numbermenor)
    {
      numbermenor = number;
    }
    repeat += 1;
  }
  printf("%i\n", numbermenor);
  return(0);
}
