#include <stdio.h>
#include <string.h>

int main()
{
  int casos, start; scanf("%d", &casos);
  for (start = 1; start <= casos; start ++)
  {
    int quantiDef, ler, check; scanf("%d", &quantiDef);
    char wordDef[quantiDef][9999]; int tempoDef[quantiDef];
    for (ler = 0; ler < quantiDef; ler ++)
    {
      getchar(); scanf("%s", wordDef[ler]);
      scanf("%d", &tempoDef[ler]);
    }
    int digit, tempo = 0; scanf("%d", &digit);
    char wordDigit[9999];
    for (ler = 0; ler < digit; ler ++)
    {
      getchar(); scanf("%s", wordDigit);
      for (check = 0; check < quantiDef; check ++)
      {
        if (strcmp(wordDigit,wordDef[check]) == 0)
        {
          tempo += tempoDef[check];
        }
      }
    }
    printf("Caso %d: %d\n", start, tempo);
  }
  return(0);
}
