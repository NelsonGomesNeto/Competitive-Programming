#include <stdio.h>
#include <string.h>
#define DEBUG if(0)
char quickBrownFox[100], quickPattern[100], table[30];

void findPattern(char string[], char pattern[])
{
  int i; char now = 'a', done[27]; memset(done, '\0', sizeof(done));
  for (i = 0; string[i] != '\0'; i++)
  {
    if (string[i] == ' ')
      pattern[i] = ' ';
    else if (done[string[i] - 'a'] == '\0')
    {
      done[string[i] - 'a'] = now + 1;
      pattern[i] = now ++;
    }
    else
      pattern[i] = done[string[i] - 'a'];
  }
}

void makeTable(char string[])
{
  int i;
  for (i = 0; string[i] != '\0'; i ++)
  {
    if (string[i] == ' ') continue;
    table[string[i] - 'a'] = quickBrownFox[i];
  }
}

int findFox(int size, char string[][81], char pattern[][81])
{
  int i;
  for (i = 0; i < size; i ++)
    if (!strcmp(pattern[i], quickPattern))
    {
      makeTable(string[i]);
      return(1);
    }

  return(0);
}

int main()
{
  strcpy(quickBrownFox, "the quick brown fox jumps over the lazy dog");
  findPattern(quickBrownFox, quickPattern);

  int tests; scanf("%d", &tests);
  getchar(); getchar();
  while (tests > 0)
  {
    char pattern[1000][81];
    memset(pattern, '\0', sizeof(pattern)); memset(table, '\0', sizeof(table));

    char string[1000][81], end; int size = 0, i, j;
    while (scanf("%c", &end) != EOF && end != '\n')
    {
      if (scanf("%[^\n]", string[size ++]+1) == EOF) break;
      string[size - 1][0] = end;
      getchar();
    }

    for (i = 0; i < size; i ++)
    {
      findPattern(string[i], pattern[i]);
      DEBUG printf("%s - %s\n", string[i], pattern[i]);
    }

    if (findFox(size, string, pattern))
    {
      for (i = 0; i < size; i ++)
      {
        for (j = 0; string[i][j] != '\0'; j ++)
          if (string[i][j] != ' ')
            string[i][j] = table[string[i][j] - 'a'];
        printf("%s\n", string[i]);
      }
    }
    else
      printf("No solution.\n");

    if (tests > 1) printf("\n");
    tests --;
  }
  return(0);
}