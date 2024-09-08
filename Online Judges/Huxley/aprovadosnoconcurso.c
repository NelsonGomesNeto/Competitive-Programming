#include <stdio.h>

int main()
{
  int pt, math, viva = 0; float red;
  while (scanf("%i", &pt) && pt >= 0)
  {
    scanf("%i\n%f", &math, &red);
    if ((float) pt / 50 >= 0.8 && (float) math / 35 >= 0.6 && red >= 7)
    {
      viva ++;
    }
  }
  printf("%i\n", viva);
  return(0);
}
