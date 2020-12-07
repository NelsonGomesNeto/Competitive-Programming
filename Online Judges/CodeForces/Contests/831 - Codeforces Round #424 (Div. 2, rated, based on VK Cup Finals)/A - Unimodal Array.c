#include <stdio.h>

int main()
{
  int size; scanf("%d", &size);
  int array[size], i;
  for (i = 0; i < size; i ++)
    scanf("%d", &array[i]);

  i = 1;
  while (i < size && array[i] > array[i - 1]) i ++;
  while (i < size && array[i] == array[i - 1]) i ++;
  while (i < size && array[i] < array[i - 1]) i ++;

  if (i == size)
    printf("YES\n");
  else
    printf("NO\n");

  return(0);
}
