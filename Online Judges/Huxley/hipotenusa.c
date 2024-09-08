#include <stdio.h>
#include <math.h>

int main()
{
  float CO, CA, H; scanf("%f\n%f", &CO, &CA);
  H = sqrt(pow(CO,2) + pow(CA,2));
  printf("%.2f\n", H);
  return(0);
}
