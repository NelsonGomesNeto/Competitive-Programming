#include <stdio.h>
#include <math.h>

int main()
{
  int vel1, vel2, aux; scanf("%d %d", &vel1, &vel2);
  int dis;  int tempo; scanf("%d", &dis);
  tempo = ((long double) (dis * 60)/ (vel2 - vel1));
  printf("%d minutos\n", (tempo));
  return(0);
}
