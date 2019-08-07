#include <stdio.h>

int main()
{
  int num, repeat, factorial = 1, soma = 0;
  for (repeat = 0; repeat < 5; repeat ++)
  {
    scanf("%i", &num);
    if (num % 3 == 0)
    {
      while (num >= 1)
      {
        factorial *= num;
        num --;
      }
      soma += factorial;
      factorial = 1;
    }
  }
  printf("%i\n", soma);
  return(0);
}
