#include <stdio.h>
#include <math.h>

int main()
{
  float num[10010], media = 0, desvio = 0; int divi = 0, notaMaior = 0, repeat;
  while (scanf("%f", &num[divi]) && num[divi] != -1)
  {
    media += num[divi];
    divi ++;
  }
  //num[divi] = 0;
  media /= (float) (divi);
  for (repeat = 0; repeat < divi; repeat ++)
  {
    if (num[repeat] > media)
    {
      notaMaior ++;
    }
  }
  for (repeat = 0; repeat < divi; repeat ++)
  {
    if (media >= num[repeat])
    {
      desvio += (float) (pow((media - num[repeat]), 2));
    }
    else
    {
      desvio += (float) (pow((num[repeat] - media), 2));
    }
  }
  desvio /= (float) divi - 1;
  desvio = sqrt(desvio);
  printf("%.2f\n%.2f\n%d\n", media, desvio, notaMaior);
  return(0);
}
