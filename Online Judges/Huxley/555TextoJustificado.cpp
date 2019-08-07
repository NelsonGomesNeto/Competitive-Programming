#include <bits/stdc++.h>
#define DEBUG if(0)
using namespace std;
int lineSize, qWord = 1, inf = 1<<20;
char words[1501][1000];
int wordSizes[1501], dp[1501][1500], path[1501][1500];

int justifiedText(int i, int midSpaces, int now)
{
  int spaces = midSpaces + (lineSize - now);
  if (i == qWord) return(spaces * spaces * spaces);

  if (dp[i][now] == -1)
  {
    int lineBreak = justifiedText(i + 1, 0, wordSizes[i]) + spaces * spaces * spaces, hold = inf;
    if (now + (now > 0) + wordSizes[i] <= lineSize)
      hold = justifiedText(i + 1, midSpaces + (now > 0), now + (now > 0)  + wordSizes[i]);
    path[i][now] = lineBreak < hold;
    dp[i][now] = min(lineBreak, hold);
  }

  return(dp[i][now]);
}

void printPath()
{
  int now = 0;
  for (int i = 0; i < qWord; i ++)
  {
    DEBUG printf("<%d, %d>\n", now, path[i][now]);
    if (path[i][now])
    {
      printf("%s\n", words[i - 1]);
      now = wordSizes[i];
    }
    else
    {
      printf("%s ", words[i]);
      now += (now > 0) + wordSizes[i];
    }
  }
}

int main()
{
  memset(dp, -1, sizeof(dp));
  memset(path, 0, sizeof(path));
  scanf("%d\n", &lineSize);
  char end;
  while (scanf("%s%c", words[qWord - 1], &end) != EOF && end != '\n') qWord ++;
  for (int i = 0; i < qWord; i ++)
  {
    wordSizes[i] = strlen(words[i]);
    DEBUG printf("%s %d\n", words[i], wordSizes[i]);
  }

  int minCost = justifiedText(0, 0, 0);
  printPath();

  return(0);
}
