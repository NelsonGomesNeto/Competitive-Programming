#include <stdio.h>
#include <string.h>

int main()
{
  char string[1000000];
  while (scanf("%[^\n]", string) != EOF)
  {
    getchar();
    int i, j, start = 0, fim = strlen(string);
    while (string[start] == ']') //Same of nothing ¬¬
    {
      start ++;
    }
    for (i = fim - 1; i >= start; i --)
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
    for (i = start; i < fim; i ++)
    {
      if ((string[i] == ']' && i != fim -1) || i == start)
      {
        j = i == start ? start : i + 1;
        while (j < fim && string[j] != '[' && string[j] != ']')
        {
          if (string[j] != '\0')
            printf("%c", string[j]);
          j ++;
        }
      }
    } printf("\n");
  }
  return(0);
}
