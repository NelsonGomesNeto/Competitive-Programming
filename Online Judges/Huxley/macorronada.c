#include <stdio.h>
#include <math.h>

int main()
{
  int testes; scanf("%d", &testes);
  while (testes > 0)
  {
    int Xi, Yi, Xf, Yf, ler, dist[3];
    for (ler = 0; ler < 3; ler ++)
    {
      scanf("%d %d %d %d", &Xi, &Yi, &Xf, &Yf);
      dist[ler] = sqrt(pow(Xi - Xf, 2) + pow (Yi - Yf, 2));
    }
    if (dist[0] + dist[1] > dist[2] && dist[0] + dist[2] > dist[1] && dist[1] + dist[2] > dist[0])
    {
      printf("SIM\n");
    }
    else
    {
      printf("NAO\n");
    }
    testes --;
  }
  return(0);
}
