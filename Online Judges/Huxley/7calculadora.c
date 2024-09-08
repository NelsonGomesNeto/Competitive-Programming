#include <stdio.h>

int main()
{
  float num1, total; char oper; int deu = 0;
  scanf("%f", &total);
  while (scanf("%f", &num1)
  && getchar() && scanf("%[^\n]", &oper) && oper != '&')
  {
    if (oper == '+')
    {
      total += num1;
    }
    else if (oper == '-')
    {
      total -= num1;
    }
    else if (oper == '*')
    {
      total *= num1;
    }
    else if (num1 != 0)
    {
      total /= num1;
    }
    else
    {
      printf("operacao nao pode ser realizada\n");
      deu ++;
    }
    if (deu == 0)
    {
      printf("%.3f\n", total);
    }
    deu = 0;
  }
  return(0);
}
