#include <stdio.h>

int romanoParaDecimal(char r[30], int d[30])
{
  int i = 0;
  for (i = 0; r[i] != '\0'; i ++)
  {
    if (r[i] == 'M')
    {
      d[i] = 1000;
    }
    if (r[i] == 'D')
    {
      d[i] = 500;
    }
    if (r[i] == 'C')
    {
      d[i] = 100;
    }
    if (r[i] == 'L')
    {
      d[i] = 50;
    }
    if (r[i] == 'X')
    {
      d[i] = 10;
    }
    if (r[i] == 'V')
    {
      d[i] = 5;
    }
    if (r[i] == 'I')
    {
      d[i] = 1;
    }
  }
  return(i);
}

int main()
{
  char num[30]; int number = 0, roman[30];
  scanf("%s", num);
  int fim = romanoParaDecimal(num, roman), i;
  for (i = 0; i < fim; i ++)
  {
    if (fim - i > 1 && roman[i] < roman[i + 1])
    {
      roman[i + 1] -= roman[i]; roman[i] = 0;
    }
    number += roman[i];
  }
  printf("%d\n", number);
  return(0);
}
