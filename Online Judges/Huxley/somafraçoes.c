#include <stdio.h>

int main()
{
  int a, b, c, d, soma, divi, repeat; scanf("%d/%d + %d/%d", &a, &b, &c, &d);
  if (b == 0 || d == 0)
  {
    printf("entrada invalida!\n");
    return(0);
  }
  soma = (d * a) + (b * c);
  divi = b * d;
  if (soma > divi)
  {
    for (repeat = 1; repeat <= soma; repeat ++)
    {
      if (soma % repeat == 0 && divi % repeat == 0)
      {
        soma /= repeat;
        divi /= repeat;
      }
    }
    for (repeat = soma; repeat > 0; repeat --)
    {
      if (soma % repeat == 0 && divi % repeat == 0)
      {
        soma /= repeat;
        divi /= repeat;
      }
    }
  }
  else
  {
    for (repeat = 1; repeat <= divi; repeat ++)
    {
      if (soma % repeat == 0 && divi % repeat == 0)
      {
        soma /= repeat;
        divi /= repeat;
      }
    }
    for (repeat = divi; repeat > 0; repeat --)
    {
      if (soma % repeat == 0 && divi % repeat == 0)
      {
        soma /= repeat;
        divi /= repeat;
      }
    }
  }
  printf("%d/%d\n", soma, divi);
  return(0);
}
