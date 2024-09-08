#include <stdio.h>

int main()
{
  int N, repeat, quant = 0, divi, divi3;
  scanf("%i", &N);
  divi = N;
  while (divi > 0)
  {
    if (N % divi == 0)
    {
      if (divi % 3 == 0)
      {
        quant ++;
      }
      divi --;
    }
    else
    {
      divi --;
    }
  }
  if (quant > 0)
  {
    printf("%i\n", quant);
  }
  else
  {
    printf("O numero nao possui divisores multiplos de 3!\n");
  }
  return(0);
}
