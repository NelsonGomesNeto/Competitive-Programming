#include <stdio.h>
#include <math.h>

int main()
{
  int caminhoes, predios; double lixo = 0; scanf("%d %d", &caminhoes, &predios);
  while (predios > 0)
  {
    long long int apartamentos, vidro, papel, plastico, metal;
    scanf("%Ld", &apartamentos);
    if (apartamentos > 0)
    {
      scanf("%Ld %Ld %Ld %Ld", &vidro, &papel, &plastico, &metal);
      lixo += (((double) vidro / 1000) + (papel) + ((double) plastico / 1000) + ((double) metal / 1000000)) * apartamentos;
    }
    predios --;
  }
  lixo /= (double) 3;
  lixo /= (double) caminhoes;
  if (caminhoes > 0)
  {
    printf("%d\n", (int) ceil(lixo));
  }
  else
  {
    printf("Nao possuem caminhoes para fazer a coleta!\n");
  }
  return(0);
}
