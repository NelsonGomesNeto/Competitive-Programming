#include <stdio.h>

int main()
{
  int carros, voltas, lerC, lerV, aux; scanf("%d %d", &carros, &voltas);
  int tempo[carros][2], lerTempo;
  for (lerC = 0; lerC < carros; lerC ++)
  {
    tempo[lerC][0] = 0;
    for (lerV = 0; lerV < voltas; lerV ++)
    {
      scanf("%d", &lerTempo);
      tempo[lerC][0] += lerTempo;
    }
    tempo[lerC][1] = lerC + 1;
    //printf("Tempo %d: %d\n", tempo[lerC][1], tempo[lerC][0]);
  }
  for (lerC = 0; lerC < carros; lerC ++)
  {
    for (lerV = 0; lerV < carros; lerV ++)
    {
      if (tempo[lerC][0] < tempo[lerV][0])
      {
        aux = tempo[lerC][0];
        tempo[lerC][0] = tempo[lerV][0];
        tempo[lerV][0] = aux;

        aux = tempo[lerC][1];
        tempo[lerC][1] = tempo[lerV][1];
        tempo[lerV][1] = aux;
      }
    }
  }
  printf("%d\n%d\n%d\n", tempo[0][1], tempo[1][1], tempo[2][1]);
  return(0);
}
