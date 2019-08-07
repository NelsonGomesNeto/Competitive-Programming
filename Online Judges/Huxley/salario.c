#include <stdio.h>

int main()
{
  int number, horas; float salary;
  scanf("%d\n%d\n%f", &number, &horas, &salary);
  salary *= horas;
  printf("NUMBER = %d\nSALARY = R$ %.2f\n", number, salary);
  return(0);
}
