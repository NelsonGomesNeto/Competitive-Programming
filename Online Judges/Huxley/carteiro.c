#include <stdio.h>

int search(int array[], int begin, int end, int toFound)
{
  if (array[(begin + end) / 2] == toFound)
  {
    return((begin + end) / 2);
  }
  else if (toFound < array[(begin + end) / 2])
  {
    search(array, begin, (begin + end) / 2, toFound);
  }
  else
  {
    search(array, (begin + end) / 2, end, toFound);
  }
}

int main()
{
  int casa, entrega; scanf("%d %d", &casa, &entrega);
  int num[casa + 20], del, ler, tempo = 0, trip = 0, carteiro = 0;
  for (ler = 0; ler < casa; ler ++)
  {
    scanf("%d", &num[ler]);
  }
  for (ler = 0; ler < entrega; ler ++)
  {
    scanf("%d", &del);
    trip = search(num, 0, casa, del);
    tempo += abs(trip - carteiro);
    carteiro = trip;
  }
  printf("%d\n", tempo);
  return(0);
}
