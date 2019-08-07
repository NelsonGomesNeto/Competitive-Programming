#include <stdio.h>

int max (int A, int B)
{
  if (A > B)
  {
    return(A);
  }
  return(B);
}

int min (int A, int B)
{
  if (A < B)
  {
    return(A);
  }
  return(B);
}

int main()
{
  int Nareas, ler, testes = 1;
  while (scanf("%d", &Nareas) && Nareas != 0)
  {
    int Xmin, Ymin, Xmax, Ymax;
    int Ye = 10000;
    int Xe = - 10000;
    int Yd = - 10000;
    int Xd = 10000;

    for (ler = 0; ler < Nareas; ler ++)
    {
      scanf("%d %d %d %d", &Xmin, &Ymin, &Xmax, &Ymax);
      Ye = min(Ye, Ymin); //Afunilação da Área.
      Xe = max(Xe, Xmin); //Afunilação da Área.
      Yd = max(Yd, Ymax); //Afunilação da Área.
      Xd = min(Xd, Xmax); //Afunilação da Área.
    }

    if (Xe < Xd && Ye > Yd)
    {
      printf("Teste %d\n%d %d %d %d\n\n", testes, Xe, Ye, Xd, Yd);
    }
    else
    {
      printf("Teste %d\nnenhum\n\n", testes);
    }
    testes ++;
  }
  return(0);
}
