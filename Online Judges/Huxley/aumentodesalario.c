#include <stdio.h>

int main()
{
  double salario;
  printf("Informe o salario do colaborador:\n");
  scanf("%lf", &salario);
  printf("Salario antes do reajuste: %g\n", salario);
  if (salario <= 280)
  {
    printf("Percentual de aumento aplicado: 20%%\n");
    printf("Valor do aumento: %.14lf\n", salario * 0.2);
    salario *= 1.2;
  }
  else if (salario <= 700)
  {
    printf("Percentual de aumento aplicado: 15%%\n");
    printf("Valor do aumento: %.14lf\n", salario * 0.15);
    salario *= 1.15;
  }
  else if (salario <= 1500)
  {
    printf("Percentual de aumento aplicado: 10%%\n");
    printf("Valor do aumento: %.14lf\n", salario * 0.1);
    salario *= 1.1;
  }
  else
  {
    printf("Percentual de aumento aplicado: 5%%\n");
    printf("Valor do aumento: %.14lf\n", salario * 0.05);
    salario *= 1.05;
  }
  printf("Salario com reajuste: %.2lf\n", salario);
  return(0);
}
