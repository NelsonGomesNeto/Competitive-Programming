#include <stdio.h>

int main()
{
  float salario; int horas;
  scanf("%f\n%i", &salario, &horas);
  salario += (salario * 0.05 * horas);
  printf("%.2f\n", salario);
  return(0);
}
