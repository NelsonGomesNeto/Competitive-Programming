#include <stdio.h>

int main()
{
  int velocidade;
  float multa;
  scanf("%i", &velocidade);
  if (velocidade > 50)
  {
    if (velocidade <= 50 * 1.1)
    {
      multa = 230.00;
    }
    else if (velocidade <= 50 * 1.2)
    {
      multa = 340.00;
    }
    else if (velocidade > 50 * 1.2)
    {
      multa = (velocidade - 50) * 19.28;
    }
    printf("%.2f\n", multa);
  }
  else
  {
    printf("0.00\n");
  }
  return(0);
}
