#include <stdio.h>

int main()
{
  int N, sorte, repetido, seq = 0, seqMaior = 0;
  scanf("%d", &N);
  while (N > 0)
  {
    scanf("%d", &sorte);
    if (seq == 0 || repetido == sorte)
    {
      seq ++;
    }
    else
    {
      if (seq > seqMaior)
      {
        seqMaior = seq;
      }
      seq = 1;
    }
    repetido = sorte;
    N --;
  }
  if (seq > seqMaior)
  {
    seqMaior = seq;
  }
  printf("%d\n", seqMaior);
  return(0);
}
