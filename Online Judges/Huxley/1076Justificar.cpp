#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

int min(int a, int b) { return(a < b ? a : b); }

void printSpaces(int spaces) { if (spaces <= 0) return; while (spaces --) printf(" "); }

int main()
{
  int n, c, i, j; scanf("%d %d", &n, &c);
  char **words = (char**) malloc(sizeof(char*) * (n + 1)); for (i = 0; i < n + 1; i ++) words[i] = (char*) malloc(sizeof(char) * (c / 2 + 1));
  int wordsSize[n + 1];
  for (i = 0; i < n; i ++)
  {
    getchar(); memset(words[i], '\0', sizeof(words[i]));
    scanf("%s", words[i]); wordsSize[i] = strlen(words[i]);
  }

  int wordsPerLine[n + 1], sum[n + 1], l = 0, k = 0, now = 0;
  memset(wordsPerLine, -1, sizeof(wordsPerLine)); memset(sum, 0, sizeof(sum));
  for (i = 0; i < n; i ++)
  {
    if (i == n - 1 || now + wordsSize[i] + k >= c)
    {
      if (now + wordsSize[i] + k <= c)
      {
        wordsPerLine[l] = k + 1, sum[l] = now + wordsSize[i];
        k = now = 0;
      }
      else
      {
        wordsPerLine[l] = k, sum[l] = now, wordsPerLine[l + 1] = 1, sum[l + 1] = wordsSize[i];
        k = 1, now = wordsSize[i];
      }
      l ++;
    }
    else k ++, now += wordsSize[i];
  }

  k = 0;
  for (i = 0; i < n && wordsPerLine[i] != -1; i ++)
  {
    int rate = (c - sum[i]) / (wordsPerLine[i] - 1), rest = (c - sum[i]) % (wordsPerLine[i] - 1);
    if (wordsPerLine[i + 1] == -1) rate = 1, rest = 0;
    // printf("%d %d %d %d %d\n", wordsPerLine[i], sum[i], c - sum[i], rate, rest);
    printf("%s", words[k ++]);
    for (j = 1; j < wordsPerLine[i]; j ++)
    {
      printSpaces(rate + (rest -- > 0));
      printf("%s", words[k ++]);
    }
    printf("\n");
  }
  return(0);
}
