#include <stdio.h>

int main()
{
  int array[20], i;
  for (i = 0; i < 20; i ++)
  {
    array[i] = i * i;
  }
  for (i = 0; i < 20; i ++)
  {
    printf("%d\n", array[i]);
  }
  return(0);
}
