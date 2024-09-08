#include <stdio.h>
int main()
{
  int min, sec, horaTotal = 0, minTotal = 0, secTotal = 0;
  while (scanf("%d\n%d", &min, &sec) != EOF)
  {
    minTotal += min;
    secTotal += sec;
  }
  if (secTotal >= 60)
  {
    minTotal += (secTotal / 60);
    secTotal %= 60;
  }
  if (minTotal >= 60)
  {
    horaTotal += (minTotal / 60);
    minTotal %= 60;
  }
  printf("%d\n%d\n%d\n", horaTotal, minTotal, secTotal);
  return(0);
}
