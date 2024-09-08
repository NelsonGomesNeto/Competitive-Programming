#include <stdio.h>

int main()
{
  printf("Compila");
  int tam; scanf("%d", &tam);
  char campo[tam + 999][tam + 999], btn, move[999];
  int snakeX = 0, snakeY = tam - 1, ler, raboX = 0, raboY = tam - 1, food = 1, posi = 0, atual = 0, rabo = 0, ini = 0;
  for (ler = 0; ler < tam; ler ++)
  {
    getchar();
    scanf("%s", campo[ler]);
  }
  //campo[snakeY][snakeX] = '*';
  getchar();
  while (scanf("%c", &btn) != EOF)
  {
    if (btn == 'C' || btn == 'B' || btn == 'D' || btn == 'E')
    {
      move[posi] = btn;
      posi ++; atual ++;
      if (btn == 'C') { snakeY -= 1; }
      else if (btn == 'B') { snakeY += 1; }
      else if (btn == 'D') { snakeX += 1; }
      else if (btn == 'E') { snakeX -= 1; }
      if (campo[snakeY][snakeX] != 'o')
      {
        campo[raboY][raboX] = '.';
        if (move[atual - food] == 'C') { raboY -= 1; }
        else if (move[atual - food] == 'B') { raboY += 1; }
        else if (move[atual - food] == 'D') { raboX += 1; }
        else if (move[atual - food] == 'E') { raboX -= 1; }
      }
      else if (campo[snakeY][snakeX] == 'o')
      {
        campo[raboY][raboX] = '*';
        food ++;
      }
      campo[snakeY][snakeX] = '*';
    }
  }

  printf("%d\n", food);
  for (ler = 0; ler < tam; ler ++)
  {
    for (food = 0; food < tam; food ++)
    {
      if (campo[ler][food] == 'o')
      {
        printf(".");
      }
      else
      {
        printf("%c", campo[ler][food]);
      }
    }
    printf("\n");
  }
  return(0);
}
