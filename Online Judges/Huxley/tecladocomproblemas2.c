#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
  char *string = calloc(1000000, sizeof(char));
  while (scanf("%[^\n]", string) != EOF)
  {
    //printf("%s\n", string);
    getchar();
    int i, j, fim = strlen(string);
    for (i = fim - 1; i >= 0; i --)
    {
      j = i;
      while (string[j] == '[' || string[j] == ']')
      {
        if (j < i)
        {
          string[j] = '\0';
        }
        j --;
      }
      j = i;
      while (string[j] == ']' || string[j] == '[')
      {
        if (j < i)
        {
          string[j] = '\0';
        }
        j --;
      }
    }
    for (i = fim - 1; i >= 0; i --)
    {
      if (string[i] == '[')
      {
        j = i + 1;
        while (j < fim && string[j] != ']' && string[j] != '[')
        {
          if (string[j] != '\0')
            printf("%c", string[j]);
          j ++;
        }
      }
    }
    for (i = 0; i < fim; i ++)
    {
      if ((string[i] == ']' && i != fim -1) || i == 0)
      {
        j = i == 0 ? 0 : i + 1;
        while (j < fim && string[j] != '[' && string[j] != ']')
        {
          if (string[j] != '\0')
            printf("%c", string[j]);
          j ++;
        }
      }
    } printf("\n");
    free(string);
    string = calloc(1000000, sizeof(char));
  }
  return(0);
}
