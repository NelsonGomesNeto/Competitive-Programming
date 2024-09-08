#include <stdio.h>
#include <math.h>

int main()
{
  int num, divi = 2; scanf("%d", &num);
  for (divi = 2; divi < sqrt(num); divi ++)
  {
    if (num % divi == 0)
    {
      printf("NAO\n");
      return(0);
    }
  }
  printf("SIM\n");
  return(0);
}
