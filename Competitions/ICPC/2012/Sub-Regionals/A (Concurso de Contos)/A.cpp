#include <bits/stdc++.h>
#define lli long long int
using namespace std;

const int maxN = 1000; int n, l, c;
char words[maxN][80]; int wordsSize[maxN];

int main()
{
  while (scanf("%d %d %d", &n, &l, &c) != EOF)
  {
    // printf("%d %d %d\n", n, l, c);
    for (int i = 0; i < n; i ++)
    {
      scanf("%s", words[i]);
      wordsSize[i] = strlen(words[i]);
    }
    // for (int i = 0; i < n; i ++)
    //   printf("%s(%d)%c", words[i], wordsSize[i], i < n - 1 ? ' ' : '\n');

    int pages = 1, nowL = 0, nowC = wordsSize[0];
    for (int i = 1; i < n; i ++)
    {
      if (nowC + 1 + wordsSize[i] <= c)
        nowC += 1 + wordsSize[i];
      else
        nowC = wordsSize[i], nowL ++;
    }
    pages += nowL / l;
    printf("%d\n", pages);
  }

  return(0);
}