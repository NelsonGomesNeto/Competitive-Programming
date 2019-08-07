#include <stdio.h>
#include <math.h>

int main()
{
  int raio; double volume, Pi = 3.14159;
  scanf("%d", &raio);
  volume = (4 * Pi * pow(raio,3)) / 3;
  printf("VOLUME = %.3lf\n", volume);
  return(0);
}
