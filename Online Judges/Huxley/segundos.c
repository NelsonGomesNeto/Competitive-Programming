#include <stdio.h>

int main()
{
  int secondsin, hourout, minout, secondsout;
  scanf("%i", &secondsin);
  hourout = secondsin / 3600;
  minout = secondsin / 60 - (hourout * 60);
  secondsout = secondsin % 60;
  printf("%i h %i m %i s\n", hourout, minout, secondsout);
  return(0);
}
