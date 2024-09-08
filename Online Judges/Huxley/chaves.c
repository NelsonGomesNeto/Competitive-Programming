#include <stdio.h>
#include <string.h>

int main()
{
  int linhas; scanf("%d", &linhas);
  int aberto = 0, valido = 1;
  while (linhas > 0)
  {
    char code[999];
    getchar();
    scanf("%[^\n]", code);
    int i;
    for (i = 0; i < strlen(code); i ++)
    {
      if (code[i] == '{')
      {
        aberto ++;
      }
      else if (code[i] == '}')
      {
        aberto --;
      }
      if (aberto < 0)
      {
        valido = 0;
      }
    }
    linhas --;
  }
  if (valido == 0 || aberto != 0)
  {
    printf("N\n");
  }
  else
  {
    printf("S\n");
  }
  return(0);
}
