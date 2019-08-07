#include <stdio.h>
#include <string.h>
#define DEBUG if(0)
char table[30];

int used(char letter)
{
  int i;
  for (i = 0; i < 30; i ++)
    if (table[i] == letter) return(1);
  return(0);
}

void findPattern(char string[], char pattern[])
{
  int i, used[27], now = 0; memset(used, 0, sizeof(used));
  for (i = 0; string[i] != '\0'; i ++)
  {
    if (!used[(int)string[i] - 'a'])
    {
      used[(int)string[i] - 'a'] = now + 1;
      pattern[i] = ++ now;
    }
    else
      pattern[i] = used[(int)string[i] - 'a'];
    DEBUG printf("%d", pattern[i]);
  } DEBUG printf("\n");
  pattern[i] = '\0';
}

int tryAll(int i, int size, char string[][20], int words, char dict[][20], char pattern[][10000][20])
{
  if (i == size)
  {
    return(1);
  }

  int k, j; char miniTable[30];
  for (k = 0; k < words; k ++)
  {
    if (!strcmp(pattern[0][k], pattern[1][i]))
    {
      strcpy(miniTable, table);
      for (j = 0; string[i][j] != '\0'; j ++)
      {
        DEBUG printf("|%s| |%s| |%c| |%c|\n", string[i], dict[k], string[i][j], dict[k][j]);
        if (table[(int)string[i][j] - 'a'] == '0' && !used(dict[k][j]))
          table[(int)string[i][j] - 'a'] = dict[k][j];
        if (table[(int)string[i][j] - 'a'] != dict[k][j])
          break;
      }
      DEBUG printf("%s\n", table);
      if (string[i][j] != '\0')
      {
        strcpy(table, miniTable);
        continue;
      }
      if (tryAll(i + 1, size, string, words, dict, pattern)) return(1);
      strcpy(table, miniTable);
    }
  }

  return(0);
}

int main()
{
  int words; scanf("%d", &words);
  char dict[words][20]; int i;
  char pattern[2][10000][20];
  for (i = 0; i < words; i ++)
  {
    getchar();
    scanf("%s", dict[i]);
    findPattern(dict[i], pattern[0][i]);
  }

  getchar();
  char string[10000][20], end; int size = 0;
  while (scanf("%s", string[size ++]) != EOF)
  {
    strcpy(table, "00000000000000000000000000\0");
    while (scanf("%c", &end) != EOF && end != '\n')
      scanf("%s", string[size ++]);

    for (i = 0; i < size; i ++)
    {
      DEBUG printf("%s ", string[i]);
      findPattern(string[i], pattern[1][i]);
    } DEBUG printf("\n");

    int j;
    if (tryAll(0, size, string, words, dict, pattern))
    {
      for (i = 0; i < size; i ++)
        for (j = 0; string[i][j] != '\0'; j ++)
          string[i][j] = table[(int) string[i][j] - 'a'];
      DEBUG printf("FOI\n");
    }
    else
      for (i = 0; i < size; i ++)
        for (j = 0; string[i][j] != '\0'; j ++)
          string[i][j] = '*';

    for (i = 0; i < size; i ++)
      printf("%s%c", string[i], i < size - 1 ? ' ' : '\n');

    size = 0;
  }

  return(0);
}