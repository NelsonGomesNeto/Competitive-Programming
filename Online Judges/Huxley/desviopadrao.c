#include <stdio.h>
#include <math.h>

int main()
{
  int n, repeat; scanf("%i", &n);
  float num[n], media = 0, desvio = 0;
  for (repeat = 0; repeat < n; repeat ++)
  {
    scanf("%f", &num[repeat]);
    media += num[repeat] / n;
  }
  for (repeat = 0; repeat < n; repeat ++)
  {
    if (media >= num[repeat])
    {
      desvio += pow((media - num[repeat]), 2) / n;
    }
    else
    {
      desvio += pow((num[repeat] - media), 2) / n;
    }
  }
  desvio = sqrt(desvio);
  printf("%.2f\n", desvio);
  return(0);
}
