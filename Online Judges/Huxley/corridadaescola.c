#include <stdio.h>

int main()
{
  int N, competidor = 1, voltas, voltasBack, tempo, total = 0, winner, winnerTime = 0;
  scanf("%i %i", &N, &voltas);
  voltasBack = voltas;
  while (competidor <= N)
  {
    while (voltasBack > 0)
    {
      scanf("%i", &tempo);
      total += tempo;
      voltasBack --;
    }
    if (total < winnerTime || winnerTime == 0)
    {
      winner = competidor;
      winnerTime = total;
    }
    total = 0;
    voltasBack = voltas;
    competidor ++;
  }
  printf("%i\n", winner);
  return(0);
}
