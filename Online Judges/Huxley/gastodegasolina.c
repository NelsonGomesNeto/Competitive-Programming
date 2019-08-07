#include <stdio.h>

int main()
{
  int tempo, speed; float gasoline;
  scanf("%i\n%i", &tempo, &speed);
  gasoline = (float) (speed * tempo) / 12;
  printf("%.3f\n", gasoline);
  return(0);
}
