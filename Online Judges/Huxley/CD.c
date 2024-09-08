#include <stdio.h>

int best[999];
int soma, max, final;

void salva(int a[], int fim)
{
  int i;
  for (i = 0; i < fim; i ++)
  {
    best[i] = a[i];
  }
  final = fim;
}

void BT(int i, int j, int resta, int CD[], int conjunto[], int tam, int total)
{
  if (resta < 0)
  {
    return;
  }
  if (total >= soma)
  {
    soma = total;
    salva(conjunto, j);
  }
  if (i == tam)
  {
    return;
  }
  BT(i + 1, j, resta, CD, conjunto, tam, total);
  conjunto[j] = CD[i];
  total += CD[i];
  resta -= CD[i];
  BT(i + 1, j + 1, resta, CD, conjunto, tam, total);
}


int main()
{
  while (scanf("%d", &max) != EOF)
  {
    int num; scanf("%d", &num);
    int CD[max], conjunto[max], ler, total;
    for (ler = 0; ler < num; ler ++)
    {
      best[ler] = -1;
      scanf("%d", &CD[ler]);
    }
    best[ler] = -1;
    soma = 0;
    BT(0, 0, max, CD, conjunto, num, 0);
    for (ler = 0; ler < final; ler ++)
    {
      printf("%d ", best[ler]);
    }
    printf("sum:%d\n", soma);
  }
  return(0);
}
