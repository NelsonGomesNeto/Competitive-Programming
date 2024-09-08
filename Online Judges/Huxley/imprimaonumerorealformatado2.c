#include <stdio.h>
#include <math.h>

int main()
{
  float num; scanf("%f", &num);
  printf("|%.2f|\n", floor(num*100)/100);
  printf("|%.5f|\n", floor(num*100000)/100000);
  printf("|      %.1f|\n", floor(num*10)/10);
  printf("|%.1f      |\n", floor(num*10)/10);
  return(0);
}
