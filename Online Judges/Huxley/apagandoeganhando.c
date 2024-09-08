#include <stdio.h>

int main()
{
  int tam, apaga;
  while (scanf("%d %d", &tam, &apaga) && !(tam == 0 && apaga == 0))
  {
    char num[tam + 1]; scanf(" %s", num); //Número de entrada
    int i = 0, prox = 1; //Atual e sucessor
    while (i < tam - 1 && apaga != 0)
    {
      if (num[i] == '9' + 1) //Ignora o número excluído
      {
        i --;
      }
      else if (num[i] < num[prox]) //Se houver sucessor maior
      {
        num[i] = '9' + 1; //Exclui o número
        apaga --; i --; //Vai voltando até achar um antecessor maior ou chegar em zero
      }
      else //Se achar um antecessor maior que o sucessor
      {
        i = prox ++; //Continua a sequência
      }
      if (i < 0) i = prox ++; //Continua a sequência
    }

    i = tam - 1; prox = tam - 2;
    while (i > 0 && apaga > 0) //Finaliza caso ainda falte número para apagar
    {
      /*if (num[i] == '9' + 1) //Ignora o número excluído
      {
        i ++;
      } else if (num[i] <= num[prox])*/ //Desnecessário!!!!
      if (num[i] <= num[prox])
      {
        num[i] = '9' + 1; //Exclui o número
        apaga --; i ++; //Vai indo até achar um "antecessor" maior ou chegar em tam
      }
      else
      {
        i = prox --; //Continua a sequência
      }
      if (i >= tam) i = prox --; //Continua a sequência
    }

    for (i = 0; i < tam; i ++) //Printa a resposta
    {
      if (num[i] <= '9') //Removendo o excluídos
        printf("%c", num[i]);
    } printf("\n");
  }
  return(0);
}
