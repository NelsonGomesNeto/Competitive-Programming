#include <stdio.h>
#include <math.h>

int main()
{
  long double num; unsigned long long int divi = 1, repeat; scanf("%Lf", &num);
  while (num > (unsigned long long int) num + 0.0000005)
  {
    num *= 10;
    //printf("~~%Lf\n", num);
    divi *= 10;
  }
  if (num > divi) //Função para simplificar!!
  {
    for (repeat = 1; repeat <= (int) num / 2; repeat ++)
    {
      if ((int) num % repeat == 0 && (int) divi % repeat == 0)
      {
        //printf("~~%Lf\n", num);
        num /= repeat;
        divi /= repeat;
      }
    }
    for (repeat = (int) num / 2; repeat > 0; repeat --)
    {
      if ((int) num % repeat == 0 && (int) divi % repeat == 0)
      {
        num /= repeat;
        divi /= repeat;
      }
    }
  }
  else //Função para simplificar!!
  {
    for (repeat = 1; repeat <= (int) divi / 2; repeat ++)
    {
      if ((int) num % repeat == 0 && (int) divi % repeat == 0)
      {
        num /= repeat;
        divi /= repeat;
      }
    }
    for (repeat = (int) divi / 2; repeat > 0; repeat --)
    {
      if ((int) num % repeat == 0 && (int) divi % repeat == 0)
      {
        num /= repeat;
        divi /= repeat;
      }
    }
  }
  printf("%d/%d\n", (int) num, (int) divi);
  return(0);
}
