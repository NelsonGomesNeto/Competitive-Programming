#include <stdio.h>
#include <string.h>

int main()
{
  int tam1, tam2, ler, maior;
  char num1[10010], num2[10010];
  scanf("%[^\n]", num1);
  getchar();
  scanf("%[^\n]", num2);
  //Lendo número 1
  int numero1[(int) strlen(num1) + 10];
  for (ler = (int) strlen(num1) - 1; ler >= 0; ler --)
  {
    numero1[(strlen(num1) - 1) - ler] = ((int) num1[ler]) - 48;
  }

  //Lendo número 2
  int numero2[(int) strlen(num2) + 10];
  for (ler = (int) strlen(num2) - 1; ler >= 0; ler --)
  {
    numero2[(strlen(num2) - 1) - ler] = ((int) num2[ler]) - 48;
  }

  //Zerando soma
  int soma[(int) strlen(num1) + (int) strlen(num2)];
  for (ler = 0; ler < (int) strlen(num1) + (int) strlen(num2); ler ++) //Zerando
  {
    soma[ler] = 0;
  }

  //Calculando soma
  if ((int) strlen(num1) >= (int) strlen(num2)) //Quando Tamanho do número 1 >= Tamanho do número 2
  {
    maior = strlen(num1);
    for (ler = 0; ler < (int) strlen(num1); ler ++) //Somando para cada casa
    {
      if (ler < (int) strlen(num2)) //Somando quando os dois tem números
      {
        soma[ler] += (numero1[ler] + numero2[ler]);
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
    maior = (int) strlen(num2);
    for (ler = 0; ler < (int) strlen(num2); ler ++)
    {
      if (ler < (int) strlen(num1)) //Somando quando os dois tem números
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
