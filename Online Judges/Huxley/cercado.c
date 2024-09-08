#include <stdio.h>
#include <math.h>

int main()
{
  int arvores, ler, check, caso = -1;
  while (scanf("%d", &arvores) != EOF) //Lê a quantidade de árvores
  {
    caso ++;
    printf("caso %d:\n", caso); //Printa o caso
    int x[arvores], y[arvores], Xesq, Yesq, dontEsq; //Posição das árvores e da árvore mais baixa à esquerda
    int VetorX, VetorY, VetorXcomp, VetorYcomp; //Vetores, para analise do ângulo
    float angulo, menor; //Ângulos
    int posX[arvores], posY[arvores], quanti = 0; //Posição das árvores que montam o cercado

    for (ler = 0; ler < arvores; ler ++)
    {
      scanf("%d %d", &x[ler], &y[ler]);
      if (ler == 0 || y[ler] <= Yesq)
      {
        if (y[ler] == Yesq && x[ler] <= Xesq)
        {
          Xesq = x[ler];
          Yesq = y[ler];
          dontEsq = ler; //Árvore que não deve ser analisada na próxima checagem
        }
        else if (y[ler] < Yesq || ler == 0)
        {
          Xesq = x[ler];
          Yesq = y[ler];
          dontEsq = ler; //Árvore que não deve ser analisada na próxima checagem
        }
      }
    }
    posX[0] = Xesq; posY[0] = Yesq; //Primeira Árvore do cercado, a mais baixa à esquerda
    printf("%d %d\n", posX[0], posY[0]); //Printa a primeira árvore

    VetorX = (Xesq + 1) - Xesq; VetorY = ((Yesq - 1) - Yesq); //Primeiro vetor, vetor genérico com a árvore

    for (check = 0; check < arvores; check ++) //Inicia a checagem pelo método: Gift Wrapping
    {
      quanti ++;
      menor = 360; //Ângulo máximo
      for (ler = 0; ler < arvores; ler ++) //Checando árvore por árvore
      {
        if (ler != dontEsq)
        {
          VetorXcomp = x[ler] - posX[quanti - 1]; VetorYcomp = y[ler] - posY[quanti - 1]; //Pegando árvore recém entrada no cercado e o x atual para achar o vetor
          angulo = (float) ((VetorX * VetorXcomp) + (VetorY * VetorYcomp)) / (sqrt(pow(VetorX,2) + pow(VetorY,2)) * sqrt(pow(VetorXcomp,2) + pow(VetorYcomp,2)));
          angulo = (float) acos(angulo) * 180 / acos(-1); //Determinado o ângulo entre duas árvores (através de vetores)
          if (angulo <= menor) //Pegando a árvore que faz o menor ângulo com o vetor base
          {
            if (angulo == menor && sqrt(pow(x[ler] - posX[quanti - 1],2) + pow(y[ler] - posY[quanti - 1],2)) > sqrt(pow(x[dontEsq] - posX[quanti - 1],2) + pow(y[dontEsq] - posY[quanti - 1],2)))
            { //Checando a existência de pontos co-lineares e definindo como cerca apenas o que tem a maior distância
              menor = angulo;
              posX[quanti] = x[ler];
              posY[quanti] = y[ler];
              dontEsq = ler; //Árvore que não deve ser analisada na próxima checagem
            }
            else if (angulo < menor)
            { //Definindo como cerca
              menor = angulo;
              posX[quanti] = x[ler];
              posY[quanti] = y[ler];
              dontEsq = ler; //Árvore que não deve ser analisada na próxima checagem
            }
          }
        }
      }
      VetorX = (posX[quanti]) - posX[quanti - 1]; VetorY = ((posY[quanti]) - posY[quanti - 1]); //Pegando o vetor base entre duas árvores-cercados (recentes)
      if (posX[quanti] == posX[0] && posY[quanti] == posY[0]) //Final da cerca, começo de um loop; necessidade de acabar com o loop
      {
        check = arvores; //Finaliza o loop
      }
      else
      {
        printf("%d %d\n", posX[quanti], posY[quanti]); //Printa cada cerca
      }
    }
    printf("\n"); // "\n" final necessário
  }
  return(0);
}

/*A ideia foi pegar o vetor base, o vetor entre a recente árvore-cerca, checar o ângulo de cada de achar o menor, definindo assim
a próxima árvore da cerca; fazendo uma espécie de relógio que gira até bater na próxima árvore da cerca*/
