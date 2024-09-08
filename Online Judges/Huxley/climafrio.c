#include <stdio.h>

int main()
{
  float temp[9], menor = 0, media = 0;
  int repeat, divi = 0;
  for (repeat = 0; repeat < 9; repeat ++)
  {
    scanf("%f", &temp[repeat]);
    if (repeat == 0 || temp[repeat] < menor)
    {
      menor = temp[repeat];
    }
    if (temp[repeat] < 0)
    {
      media += temp[repeat];
      divi ++;
    }
  }
  media /= divi;
  printf("%.2f\n%.2f\n", menor, media);
  return(0);
}
