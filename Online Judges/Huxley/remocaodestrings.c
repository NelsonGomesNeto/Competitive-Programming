#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int tam, ans;

char* remov(char s[], int at, int fim)
{
  int i = at; char *new = malloc(26 * sizeof(char));
  while (i + 1 < fim && s[i] == s[i + 1])
  {
    i ++;
  }
  int end = i; int j;
  for (i = 0, j = 0; i < fim; i ++)
  {
    if (i < at || i > end)
    {
      new[j] = s[i];
      j ++;
    }
  }
  return(new);
}

void dp(char s[], int rest)
{
  if (ans == 1) { return; }
  if (rest == 0)
  {
    ans = 1;
    return;
  }
  int i;
  for (i = 0; i < rest; i ++)
  {
    if (i + 1 < rest && s[i] == s[i + 1])
    {
      char aux[26]; strcpy(aux, remov(s, i, rest));
      int newTam = strlen(aux);
      dp(aux, newTam);
    }
  }
}

int main()
{
  int tests, run; scanf("%d", &tests);
  for (run = 1; run <= tests; run ++)
  {
    getchar();
    char string[26]; scanf("%s", string);
    tam = strlen(string);
    ans = 0;
    dp(string, tam);
    printf("%d\n", ans);
  }
  return(0);
}
