#include <bits/stdc++.h>

int main()
{
  int n, l, c; scanf("%d %d %d\n", &n, &l, &c);
  int wordsSize[n], inLine = 0, lines = 1, pages = 1, first = 1;
  char words[n][c + 1];
  for (int i = 0; i < n; i ++)
  {
    scanf("%s", words[i]); getchar();
    wordsSize[i] = strlen(words[i]);
    inLine += (!first) + wordsSize[i];
    first = 0;
    if (inLine > c)
    {
      inLine = wordsSize[i];
      first = 0;
      lines ++;
    }
    if (lines > l)
    {
      lines = 1;
      pages ++;
    }
  }

  printf("%d\n", pages);

  return(0);
}