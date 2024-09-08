#include <stdio.h>

int best, tam; //Custo do melhor caminho e tamanho da matriz

int min(int a, int b) //Apenas retorna o melhor caminho
{
  return(a < b ? a : b);
}

//Salva o melhor caminho simplesmente percorrendo a matriz da DP;
/*Eu diria que a DP é como se fosse uma derivada, onde você pode
com certeza basear-se para percorrer simplesmente*/
void saveThisPath(int field[][tam + 1], int thePath[])
{
  int y, x, start, menor = -1, coluna; //Variaveis de controle
  for (x = 0; x < tam; x ++) //Acha pode onde ele deve começar
  {
    if (menor == -1 || (field[0][x] < menor && field[0][x] != -1))
    {
      menor = field[0][x];
      start = x;
    }
  }
  thePath[0] = start;
  for (y = 1; y < tam; y ++) //De lá, ele percorre a matriz de forma simples:
  {
    menor = -1;
    for (x = start - 1; x < start + 2; x ++) //Apenas procurando o menor, seguindo
    {
      if (x >= 0 && x < tam)
      {
        if (menor == -1 || (field[y][x] < menor && field[y][x] != -1))
        {
          menor = field[y][x];
          coluna = x;
        }
      }
    }
    thePath[y] = coluna; //e salvando
    start = coluna;
  }
}

//Acha o melhor caminho usando recursão e DP
int backtrack(int m[][tam], int i, int j, int bestP[], int dp[][tam + 1])
{
  if (i == tam) //Parada da recursão
    return(0);

  if (dp[i][j] == -1) //Caso não saiba o valor do melhor caminho, ele o define:
  {
    dp[i][j] = backtrack(m, i + 1, j, bestP, dp) + m[i][j]; //Indo reto
    if (j - 1 >= 0) //Virando para esquerda
      dp[i][j] = min(dp[i][j], backtrack(m, i + 1, j - 1, bestP, dp) + m[i][j]);
    if (j + 1 < tam) //Virando para direita
      dp[i][j] = min(dp[i][j], backtrack(m, i + 1, j + 1, bestP, dp) + m[i][j]);
  }

  if (i == 0 && dp[0][j] < best) //Se for melhor:
    saveThisPath(dp, bestP); //Ele salva esse caminho

  return(dp[i][j]); //Retorna quanto custou esse melhor caminho
}

int main()
{
  scanf("%d", &tam);
  int m[tam][tam], dp[tam + 1][tam + 1], bestPath[tam], i, j;

  for (i = 0; i < tam; i ++) //Lê o caminho e prepara a DP
  {
    for (j = 0; j < tam; j ++)
    {
      scanf("%d", &m[i][j]);
      dp[i][j] = -1;
    } //dp[i][j + 1] = -1;
  }
  /*for (j = 0; j < tam; j ++)
  {
    dp[i][j] = -1;
  }*/

  best = 999999;
  for (j = 0; j < tam; j ++) //Inicia a busca pelo melhor caminho
  {
    best = min(best, backtrack(m, 0, j, bestPath, dp));
  }

  printf("%d\n", best); //Printa o melhor caminho
  for (i = tam - 1; i >= 0; i --)
  {
    printf("[%d,%d]", i, bestPath[i]);
    if (i != 0)
    {
      printf(" <- ");
    }
  } printf("\n");
  return(0);
}
