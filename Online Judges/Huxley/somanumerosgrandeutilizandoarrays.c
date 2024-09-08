#include <stdio.h>

int main()
{
  int tam1, tam2, ler, maior;
  //Lendo número 1
  scanf("%d", &tam1);
  int numero1[tam1];
  for (ler = tam1 - 1; ler >= 0; ler --)
  {
    scanf("%d", &numero1[ler]);
  }
  //Lendo número 2
  scanf("%d", &tam2);
  int numero2[tam2];
  for (ler = tam2 - 1; ler >= 0; ler --)
  {
    scanf("%d", &numero2[ler]);
  }
  //Zerando soma
  int soma[tam1 + tam2];
  for (ler = 0; ler < tam1 + tam2; ler ++) //Zerando
  {
    soma[ler] = 0;
  }

  //Calculando soma
  if (tam1 >= tam2) //Quando Tamanho do número 1 >= Tamanho do número 2
  {
    maior = tam1;
    for (ler = 0; ler < tam1; ler ++) //Somando para cada casa
    {
      if (ler < tam2) //Somando quando os dois tem números
      {
        soma[ler] += numero1[ler] + numero2[ler];
      }
      else //Somando quando só um tem número
      {
        soma[ler] += numero1[ler];
      }
      if (soma[ler] > 9) //Corrigindo se dígito for > 9
      {
        soma[ler + 1] += soma[ler] / 10;
        soma[ler] %= 10;
      }
    }
  }
  else //Quando Tamanho do número 2 >= Tamanho do número 1
  {
    maior = tam2;
    for (ler = 0; ler < tam2; ler ++)
    {
      if (ler < tam1) //Somando quando os dois tem números
      {
        soma[ler] += numero1[ler] + numero2[ler];
      }
      else //Somando quando só um tem número
      {
        soma[ler] += numero2[ler];
      }
      if (soma[ler] > 9) //Corrigindo se dígito for > 9
      {
        soma[ler + 1] += soma[ler] / 10;
        soma[ler] %= 10;
      }
    }
  }
  //Printando a soma
  if (soma[maior] < 10 && soma[maior] > 0) //Se tem um dígito a mais (9 + 1 = 10)
  {
    for (ler = maior; ler >= 0; ler --)
    {
      printf("%d", soma[ler]);
    }
  }
  else //Se tem a mesma quantidade de dígitos
  {
    for (ler = maior - 1; ler >= 0; ler --)
    {
      printf("%d", soma[ler]);
    }
  }
  printf("\n");
  return(0);
}
