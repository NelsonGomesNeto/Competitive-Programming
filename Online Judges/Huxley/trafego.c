#include <stdio.h>

void printar(int matriz[4][4])
{
  int i, j;
  for (j = 0; j < 4; j ++)
  {
    for(i = 0; i < 4; i ++)
    {
      printf("%d ", matriz[i][j]);
    }
    printf("\n");
  }
}

int main()
{
  int origem, destino, tipo, carro[4][4], caminhao[4][4], onibus[4][4], belos = 0, petro = 0;
  for (tipo = 0; tipo < 4; tipo ++)
  {
    for(origem = 0; origem < 4; origem ++)
    {
      carro[origem][tipo] = 0;
      caminhao[origem][tipo] = 0;
      onibus[origem][tipo] = 0;
    }
  }
  while (scanf("%d %d %d", &origem, &destino, &tipo) && !(origem == 0 && destino == 0 && tipo == 0))
  {
    if (tipo == 1)
    {
      carro[destino - 1][origem - 1] ++;
    }
    else if (tipo == 2)
    {
      caminhao[destino - 1][origem - 1] ++;
    }
    else
    {
      onibus[destino - 1][origem - 1] ++;
    }
    if (origem == 1)
    {
      belos ++;
    }
    if (tipo == 3 && origem == 4 && (destino == 2 || destino == 4))
    {
      petro ++;
    }
  }
  printf("Automovel:\n"); printar(carro);
  printf("Caminhao:\n"); printar(caminhao);
  printf("Onibus:\n"); printar(onibus);
  printf("Origem Belo Horizonte: %d\n", belos);
  printf("Onibus: Brasilia - Petropolis ou Barbacena: %d\n", petro);
  return(0);
}
