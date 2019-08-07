#include <stdio.h>

int main()
{
  char string[6];
  scanf("%[^\n]", string);
  int i, j;
  for (i = 0, j = 4; i < 5; i ++, j --)
  {
    if (string[i] != string[j])
    {
      printf("N\n");
      return(0);
    }
  }
  printf("S\n");
  return(0);
}
