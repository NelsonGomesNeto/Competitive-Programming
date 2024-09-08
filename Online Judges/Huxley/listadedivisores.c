#include <stdio.h>

int main()
{
  int num, divi = 1; scanf("%d", &num);
  while (divi <= num)
  {
    if (num % divi == 0)
    {
      printf("%d\n", divi);
    }
    divi ++;
  }
  return(0);
}
