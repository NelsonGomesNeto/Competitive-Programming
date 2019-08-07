#include <stdio.h>
#include <math.h>

int num, a[5], sol;

int check(int atual, int fim)
{
  int i;
  for (i = 0; i < fim; i ++)
    if (a[i] == atual)
      return(0);

  return(1);
}

int end = 0;

void bt(int i)
{
  if (end == 1) return; //Finaliza a recursão 

  if (i == 5) //Terminou de gerar o divisor
  {
    //Transforma o array gerado em número (gerado)
    int k; int n = 0, divi = 0, decay = 10000;
    for (k = 0; k < 5; k ++)
    {
      divi += (a[k] * decay);
      decay /= 10;
    }

    //Multiplica a entrada pelo divisor gerador
    n = divi * num; //Tem-se o numerador
    if (n > 98765)
    { //Se for maior que o limite,
      end = 1; //Exita da recusão toda
      return;
    }

    //Separa o número (resultante da multiplicação) em um array
    int aux, test[5]; decay = 10000;
    for (k = 0; k < 5; k ++)
    {
      aux = (n / decay) % 10;
      test[k] = aux;

      if (check(aux, 5) == 0) //Verifica se nenhum dígito está no primeiro gerado
        return;

      decay /= 10;
    }

    //Verifica se nenhum dígito se repete no primeiro e no segundo
    int x;
    for (k = 0; k < 5; k ++)
      for (x = 0; x < 5; x ++)
        if (test[k] == test[x] && x != k)
          return;

    sol = 1; //Teve solução
    if (divi < 10000) //Printa a solução
    {
      printf("%d / 0%d = %d\n", n, divi, num);
    }
    else //Printa a solução
    {
      printf("%d / %d = %d\n", n, divi, num);
    }

    return;
  }

  //Gera um número (O divisor)
  int j;
  for (j = 0; j < 10; j ++)
  {
    if (check(j, i) == 1) //Verifica se nenhum dígito irá se repetir
    {
      a[i] = j;
      bt(i + 1); //Chama recursiva
    }
  }
}

int main()
{
  int run = 0;
  while (scanf("%d", &num) && num != 0)
  {
    if (run > 0)
      printf("\n");

    run ++;
    sol = 0; end = 0;
    bt(0);

    if (sol == 0)
      printf("There are no solutions for %d.\n", num);
  }
  return(0);
}
