#include <stdio.h>
#include <time.h>
#include <algorithm>
using namespace std;
int search(int a[], int num, int xI, int xF)
{
  if (num == a[(xF + xI) / 2])
  {
    return((xF + xI) / 2);
  }
  else if (num < a[(xF + xI) / 2])
  {
    search(a, num, xI, (xF + xI) / 2);
  }
  else
  {
    search(a, num, (xF + xI) / 2, xF);
  }
}

int main()
{
  int array[1000000], se, tam = 0;
  int i, posi;
  for (i = 0; i < 1000000; i ++)
  {
    scanf("%d", &array[i]);
  }
  clock_t elapsed = clock();
  sort(array, array + 1000000);
  for (i = 0; i < 1000000; i ++)
  {
    posi = search(array, i, 0, 1000000);
  }
  elapsed = (clock() - elapsed);
  printf("%d found at %d in: %lf\n", array[posi], posi, ((double) elapsed)/CLOCKS_PER_SEC);
  return(0);
}
