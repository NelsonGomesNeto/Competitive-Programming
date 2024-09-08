#include <stdio.h>
#include <string.h>

int main()
{
  int linhas; scanf("%d", &linhas);
  while (linhas > 0)
  {
    int paren = 0, chave = 0, aberto, i, j, valido = 1;
    char string[999], pilha[999];
    for (i = 0; i < 999; i ++)
    {
      pilha[i] = '\0';
      string[i] = '\0';
    }
    getchar();
    scanf("%[^\n]", string);
    for (i = 0, j = 0; i < strlen(string); i ++)
    {
      if (string[i] == '[')
      {
        chave ++; pilha[j] = string[i];
        j ++;
      }
      else if (string[i] == ']')
      {
        j --;
        if (pilha[j] != '[')
        {
          valido = 0;
        }
        chave --; pilha[j] = '\0';
      }
      else if (string[i] == '(')
      {
        paren ++; pilha[j] = string[i];
        j ++;
      }
      else if (string[i] == ')')
      {
        j --;
        if (pilha[j] != '(')
        {
          valido = 0;
        }
        paren --; pilha[j] = '\0';
      }
      if (paren < 0 || chave < 0)
      {
        valido = 0;
      }
    }
    if (valido == 0 || paren != 0 || chave != 0)
    {
      printf("No\n");
    }
    else
    {
      printf("Yes\n");
    }
    linhas --;
  }
  return(0);
}
