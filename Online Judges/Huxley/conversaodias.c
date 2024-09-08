#include <stdio.h>

int main()
{
  int diasint, anoout, mesout, diasout;
  scanf("%i", &diasint);
  anoout = diasint / 365;
  mesout = (diasint - (anoout * 365)) / 30;
  diasout = (diasint - (anoout * 365)) % 30;
  printf("%i ano(s)\n%i mes(es)\n%i dia(s)\n", anoout, mesout, diasout);
  return(0);
}
