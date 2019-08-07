#include <stdio.h>

int main()
{
  float velM, velV, multa;
  int pontos;
  scanf("%f\n%f", &velM, &velV);
  if ((velV > velM) && (velV <= velM * 1.2))
  {
    multa = 85.13;
    pontos = 4;
    printf("%.2f\n%i\n", multa, pontos);
  }
  else if ((velV > velM * 1.2) && (velV <= velM * 1.5))
  {
    multa = 127.69;
    pontos = 5;
    printf("%.2f\n%i\n", multa, pontos);
  }
  else if (velV > velM * 1.5)
  {
    multa = 574.62;
    pontos = 7;
    printf("%.2f\n%i\n", multa, pontos);
  }
  else
  {
    multa = 0.00;
    pontos = 0;
    printf("%.2f\n%i\n", multa, pontos);
  }
  return(0);
}
