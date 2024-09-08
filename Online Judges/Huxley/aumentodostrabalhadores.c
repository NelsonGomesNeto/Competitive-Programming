#include <stdio.h>

int main()
{
  float salario, aumento;
  scanf("%f", &salario);
  if (salario > 500)
  {
    aumento = salario + (salario * 0.1);
  }
  else if (salario > 300 && salario <= 500)
  {
    aumento = salario + (salario * 0.07);
  }
  else
  {
    aumento = salario + (salario * 0.05);
  }
  printf("%.2f\n", aumento);
  return(0);
}
