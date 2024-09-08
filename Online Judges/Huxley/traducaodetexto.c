#include <stdio.h>
#include <string.h>

int main()
{
  int n, repeat, first, posi; scanf("%d", &n);
  char word[(n * 2)][99], frase[999], *traduz, fim[999] = "";
  for (repeat = 0; repeat < (n * 2); repeat += 2)
  {
    getchar();
    scanf("%s => %s", word[repeat], word[repeat + 1]);
  }
  while (getchar() && scanf("%[^\n]", frase) && frase[0] != '*')
  {
    posi = 0;
    first = 0;
    traduz = strtok(frase," ");
    strcpy(fim,"");
    while (traduz != NULL)
    {
      if (first > 0)
      {
        traduz = strtok(NULL," ");
      }
      first ++; repeat = 0;
      while (traduz != NULL && strcmp(traduz,word[repeat]) != 0)
      {
        repeat += 2;
      }
      if (traduz != NULL)
      {
        strcat(fim, word[repeat + 1]);
        strcat(fim," ");
      }
    }
    fim[strlen(fim) - 1] = '\n';
    printf("%s", fim);
  }
  return(0);
}
