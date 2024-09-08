#include <stdio.h>

int main()
{
  int N, Time, Speed, distance = 0;
  scanf("%i", &N);
  while (N > 0)
  {
    scanf("%i\n%i", &Time, &Speed);
    distance += (Time * Speed);
    N --;
  }
  printf("%i\n", distance);
  return(0);
}
