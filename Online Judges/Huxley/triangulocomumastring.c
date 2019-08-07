#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main()
{
  char string[100];
  while (scanf("%[^\n]", string) != EOF)
  {
    getchar();
    int tam = strlen(string);
    if (tam < 1 || tam > 20)
    {
      printf("Entrada invalida\n");
      continue;
    }
    int i, j;
    for (i = 0; string[i] != '\0'; i ++)
    {
      for (j = 0; j <= i; j ++)
      {
        printf("%c", toupper(string[i]));
      } printf("\n");
    }
    return(0);
  }
}
