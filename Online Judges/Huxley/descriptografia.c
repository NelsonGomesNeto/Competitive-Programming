#include <stdio.h>

int main()
{
  char string[200];
  scanf("%[^\n]", string);
  int i, aberto = 0;
  for (i = 0; string[i] != '\0'; i ++)
  {
    if (string[i] == '*')
    {
      printf("(");
      aberto ++;
    }
    printf("%d", i + 1);
  }
  while (aberto > 0)
  {
    printf(")");
    aberto --;
  }
  printf("\n");
  return(0);
}
