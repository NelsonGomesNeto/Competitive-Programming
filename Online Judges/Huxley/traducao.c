#include <stdio.h>
#include <string.h>

int main()
{
  int n, repeat, first, posi, frases, aux, foi;
  while (scanf("%d %d", &n, &frases) != EOF)
  {
    char word[(n * 2)][99], frase[999], meio[999], fim[999];
    for (repeat = 0; repeat < (n * 2); repeat += 2)
    {
      getchar();
      scanf("%s -> %s", word[repeat], word[repeat + 1]);
    }
    while (getchar() && scanf("%[^\n]", frase) && frases > 0)
    {
      aux = 0;
      while (aux < strlen(frase))
      {
        for (n = 0; n < 999; n ++)
        {
          meio[n] = '\0';
        }
        foi = 0;
        for (posi = 0; frase[aux] != ' '; posi ++)
        {
          meio[posi] = frase[aux];
          aux ++;
        }
        aux ++;
        for (first = 0; first < repeat && foi == 0; first += 2)
        {
          if (strcmp(meio,word[first]) == 0 && aux < strlen(frase))
          {
            printf("%s ", word[first + 1]);
            foi ++;
          }
          else if (strcmp(meio,word[first]) == 0)
          {
            printf("%s\n", word[first + 1]);
            foi ++;
          }
        }
        if (foi == 0 && aux < strlen(frase))
        {
          printf("%s ", meio);
        }
        else if (foi == 0)
        {
          printf("%s\n", meio);
        }
      }
      strcpy(frase,"");
      //printf("%s\n", fim);
      frases --;
    }
  }
  return(0);
}
