#include <stdio.h>

int main()
{
  int hour, min;
  scanf("%i\n%i", &hour, &min);
  min = min + hour * 60;
  printf("%i minutos.\n", min);
  return(0);
}
