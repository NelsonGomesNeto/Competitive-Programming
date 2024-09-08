#include <stdio.h>

int main()
{
  int N1, N2, N3, N4, N5, aux;
  scanf("%d %d %d %d %d", &N1, &N2, &N3, &N4, &N5);
  if (N1 > N2)
  {
    aux = N1;
    N1 = N2;
    N2 = aux;
  }
  if (N2 > N3)
  {
    aux = N2;
    N2 = N3;
    N3 = aux;
  }
  if (N3 > N4)
  {
    aux = N3;
    N3 = N4;
    N4 = aux;
  }
  if (N4 > N5)
  {
    aux = N4;
    N4 = N5;
    N5 = aux;
  }
  if (N1 > N2)
  {
    aux = N1;
    N1 = N2;
    N2 = aux;
  }
  if (N2 > N3)
  {
    aux = N2;
    N2 = N3;
    N3 = aux;
  }
  if (N3 > N4)
  {
    aux = N3;
    N3 = N4;
    N4 = aux;
  }
  if (N1 > N2)
  {
    aux = N1;
    N1 = N2;
    N2 = aux;
  }
  if (N2 > N3)
  {
    aux = N2;
    N2 = N3;
    N3 = aux;
  }
  if (N1 > N2)
  {
    aux = N1;
    N1 = N2;
    N2 = aux;
  }
  printf("1 - %d km/h\n", N5);
  printf("2 - %d km/h\n", N4);
  printf("3 - %d km/h\n", N3);
  printf("4 - %d km/h\n", N2);
  printf("5 - %d km/h\n", N1);
  return(0);
}
