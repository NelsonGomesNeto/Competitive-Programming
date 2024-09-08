#include <stdio.h>

int N1, N2, resto1, resto2, repeat;

int potencia1(int x1, int y1)
{
  int number1;

  if (y1 == 0)
  {
    return(1);
  }

  number1 = potencia1(x1, y1 / 2) % 100;

  if (y1 % 2 != 0)
  {
    return ((((x1 * number1) % 100) * number1) % 100);
  }

  return ((number1 * number1) % 100);
}

int potencia2(int x2, int y2)
{
  int number2;

  if (y2 == 0)
  {
    return(1);
  }

  number2 = potencia2(x2, y2 / 2) % 100;

  if (y2 % 2 != 0)
  {
    return ((((x2 * number2) % 100) * number2) % 100);
  }

  return ((number2 * number2) % 100);
}

/*int potencia2(int repeat)
{
  if (repeat < 1)
  {
    return(1);
  }
  else
  {
    return((potencia2(repeat - 1) * resto2) % 100);
  }
}*/

int main()
{
  while (scanf("%d %d", &N1, &N2) != EOF)
  {
    resto1 = N1 % 100;
    repeat = N1;
    resto1 = potencia1(resto1, repeat);
    resto2 = N2 % 100;
    repeat = N2;
    resto2 = potencia2(resto2, repeat);
    if (resto1 > resto2)
    {
      printf("%d\n", N1);
    }
    else if (resto2 > resto1)
    {
      printf("%d\n", N2);
    }
    else
    {
      printf("0\n");
    }
  }
  return(0);
}
