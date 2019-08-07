#include <stdio.h>

void swap(int *n1, int *n2)
{
  int aux;
  aux = *n1;
  *n1 = *n2;
  *n2 = aux;
}

int main()
{
  int num1, num2, num3;
  scanf("%d %d %d", &num1, &num2, &num3);
  if (num1 > num2)
  {
    swap(&num1, &num2);
  }
  if (num2 > num3)
  {
    swap(&num2, &num3);
  }
  if (num1 > num2)
  {
    swap(&num1, &num2);
  }
  printf("%d eh o maior\n", num3);
  return(0);
}
