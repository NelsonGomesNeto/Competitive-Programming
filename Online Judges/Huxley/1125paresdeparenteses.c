#include <stdio.h>

void fill(char string[], int stack, int i, int size, int *newest)
{
  //printf("i: %d, stack: %d, string: %s\n", i, stack, string);
  if (i == size)
  {
    if (!(*newest))
      printf(", ");

    (*newest) = 0;

    string[i] = '\0';
    printf("%s", string);
    return;
  }

  if (stack + 1 <= size - i)
  {
    string[i] = '(';
    fill(string, stack + 1, i + 1, size, &(*newest));
  }
  if (stack - 1 >= 0)
  {
    string[i] = ')';
    fill(string, stack - 1, i + 1, size, &(*newest));
  }
}

int main()
{
  int number; scanf("%d", &number);

  char string[number * 2 + 10];
  int newest = 1;
  printf("["); fill(string, 0, 0, number * 2, &newest); printf("]\n");

  return(0);
}
