#include <stdio.h>

void lendo(float *porcen, int limit)
{
  int ler;
  for (ler = 0; ler < limit; ler ++)
  {
    scanf("%f", &porcen[ler]);
  }
}
int main()
{
  int votos, check, todos; scanf("%d", &votos);
  float candidato[votos], concorrente[votos], maior;
  lendo(candidato, votos); lendo(concorrente, votos);
  for (check = 0; check < votos; check ++)
  {
    if (check == 0 || maior < candidato[check] - concorrente[check])
    {
      maior = candidato[check] - concorrente[check];
    }
  }
  if (maior >= 0)
  {
    printf("%.2f\n", maior);
  }
  else { printf("0.00\n"); }
  return(0);
}
