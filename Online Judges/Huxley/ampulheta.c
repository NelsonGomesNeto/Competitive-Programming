#include <stdio.h>

int main()
{
  int testes, repeat; scanf("%d", &testes);
  int tamanho, tempo = 1, drawX, drawY, meio;
  for (repeat = 1; repeat <= testes; repeat ++)
  {
    meio = 2;
    scanf("%d%d", &tamanho, &tempo);
    printf("Caso %d:\n", repeat);
    for (drawY = 0; drawY < tamanho * 2; drawY ++) //Desenha o Triângulo
    {
      printf("*");
      for (drawX = 0; drawX < (tamanho * 2) - 1; drawX ++)
      {
        if (drawY == tamanho && meio > 1) //Meio
        {
          for (drawX = 0; drawX < (tamanho * 2) - 1; drawX ++)
          {
            if (drawX == drawY - 1)
            {
              printf("*");
            }
            else
            {
              printf(" ");
            }
          }
          meio --;
        }
        else if ((drawX == drawY + (meio - 2) || drawX == (tamanho * 2) - (drawY + meio))) //Borda
        {
          printf("*");
        }
        else
        {
          if (drawY == 0 || drawY == (tamanho * 2) - 1) //Topo
          {
            if (drawX % 2 != 0)
            {
              printf(" ");
            }
            else
            {
              printf("*");
            }
          }
          else
          {
            if ((drawY > (tamanho * 2) - (tempo + 2) &&
            (drawX < drawY &&
            drawX >= (tamanho * 2) - (drawY)))) //Tempo Inferior
            {
              printf(".");
            }
            else
            {
              if ((drawY > (tamanho - (tamanho - tempo)) && drawY < tamanho) &&
              (drawX > drawY &&
              drawX < (tamanho * 2) - (drawY + 1))) //Tempo Superior
              {
                printf(".");
              }
              else
              {
                printf(" ");
              }
            }
          }
        }
      }
      if (drawY < (tamanho * 2) - 1) //Baixo
      {
        printf("*\n");
      }
      else
      {
        printf("*\n");
      }
    }
  }
  return(0);
}
