#include <stdio.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;

int main()
{
  int array[10010], i = 0;
  while (scanf("%d", &array[i]) != EOF)
  {
    sort(array, array + i + 1);
    i ++; int meri; int o, b, aux;
    if (i % 2 == 0)
    {
      meri = (array[i / 2] + array[(i / 2) - 1]) / 2;
    }
    else
    {
      meri = array[(i - 1) / 2];
    }
    printf("%d\n", meri);
  }
  return(0);
}
