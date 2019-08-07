#include <stdio.h>

int main()
{
  int obj; scanf("%d", &obj);
  int A[obj + 10], B[obj + 10], ler, o, b, aux, min, max, foto = 0, pic = 0;
  for (ler = 0; ler < obj; ler ++)
  {
    scanf("%d %d", &A[ler], &B[ler]);
  }
  for (o = 0; o < obj; o ++)
  {
    for (b = o; b < obj; b ++)
    {
      if (A[o] > A[b])
      {
        aux = A[o];
        A[o] = A[b];
        A[b] = aux;

        aux = B[o];
        B[o] = B[b];
        B[b] = aux;
      }
    }
  }
  aux = obj;
  while (aux > 0)
  {
    //printf("%d %d\n", A[0], B[0]);
    min = A[foto]; max = B[foto];
    o = foto;
    while (A[o] >= min && A[o] <= max)
    {
      A[o] = 0; B[o] = 0;
      o ++;
      aux --;
      foto ++;
    }
    pic ++;
  }
  printf("%d\n", pic);
  return(0);
}
