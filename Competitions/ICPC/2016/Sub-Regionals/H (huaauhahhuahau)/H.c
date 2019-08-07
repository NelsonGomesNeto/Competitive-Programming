#include <stdio.h>
#include <stdbool.h>

bool isVogal(char letter)
{
  return(letter == 'a' || letter == 'e' || letter == 'i'
      || letter == 'o' || letter == 'u');
}

int main()
{
  char string[100], read; int i = 0;
  while (scanf("%c", &read) != EOF)
    if (isVogal(read))
      string[i ++] = read;

  int end = i, j;
  for (i = 0, j = end - 1; i < end; i ++, j --)
    if (string[i] != string[j])
    {
      printf("N\n"); return(0);
    }

  printf("S\n");
  return(0);
}
