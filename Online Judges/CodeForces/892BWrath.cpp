#include <bits/stdc++.h>

int main()
{
  int guilty;
  while (scanf("%d", &guilty) != EOF)
  {
    int g[guilty];
    for (int i = 0; i < guilty; i ++)
      scanf("%d", &g[i]);

    int killed = 0, saved = 0, wave = 0;
    for (int i = guilty - 1; i >= 0; i --, wave -= wave > 0)
    {
      if (!wave) saved ++;
      if (g[i] + 1 > wave) wave = g[i] + 1;
      if (wave) killed ++;
      //printf("%d %d %d\n", i, wave, saved);
    }

    printf("%d\n", saved);
  }

  return(0);
}