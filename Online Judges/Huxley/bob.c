#include <stdio.h>

int binS(int a[], int start, int end, int wanted)
{
  if (start > end) { return(-1); }
  int mid = (end + start) / 2;
  if (wanted < a[mid])
  {
    return(binS(a, start, mid - 1, wanted));
  }
  if (wanted > a[mid])
  {
    return(binS(a, mid + 1, end, wanted));
  }
  return(mid);
}

int procuraNum(int ar[], int start, int end, int wanted)
{
  int pos = binS(ar, start, end, wanted);
  if (pos == -1) { return(0); }
  int quantidade = 1, i = pos + 1;
  while (i <= end && ar[i] == wanted)
  {
    quantidade ++; i ++;
  }
  i = pos - 1;
  while (i >= start && ar[i] == wanted)
  {
    quantidade ++; i --;
  }
  return(quantidade);
}

int main()
{
  int testes, caso = 1; scanf("%d", &testes);
  while (caso <= testes)
  {
    printf("caso %d:\n", caso);
    int tam, num, asks; scanf("%d %d", &tam, &asks);
    int array[tam], i;
    for (i = 0; i < tam; i ++)
    {
      scanf("%d", &array[i]);
    }
    while (asks > 0)
    {
      scanf("%d", &num);
      int aparicoes = procuraNum(array, 0, tam - 1, num);
      printf("%d\n", aparicoes);
      asks --;
    }
    caso ++;
  }
  return(0);
}
