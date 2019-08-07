#include <stdio.h>

void fill(char string[], int i, int size)
{
  if (i == size)
  {
    string[size] = '\0';
    printf("%s\n", string);
    return;
  }

  string[i] = '0';
  fill(string, i + 1, size);
  if (i == 0 || string[i - 1] != '1')
  {
    string[i] = '1';
    fill(string, i + 1, size);
  }
}

int main()
{
  int size; scanf("%d", &size);
  char string[size + 1];
  fill(string, 0, size);

  return(0);
}