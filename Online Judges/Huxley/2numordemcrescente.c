#include <stdio.h>

int main()
{
  int num1, num2;
  scanf("%i %i", &num1, &num2);
  if (num1 >= num2)
  {
    printf("%i %i\n", num2, num1);
  }
  else
  {
    printf("%i %i\n", num1, num2);
  }
  return(0);
}
