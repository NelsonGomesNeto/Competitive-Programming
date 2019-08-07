#include <bits/stdc++.h>

int main()
{
  int n, t = 0;
  while (scanf("%d", &n) && n)
  {
    if (t) printf("\n");
    int password[6], pool[6][10]; memset(pool, 0, sizeof(pool));
    for (int i = 0; i < n; i ++)
    {
      int crypt[5][2];
      for (int j = 0; j < 5; j ++)
        scanf("%d %d", &crypt[j][0], &crypt[j][1]);
      char letter;
      for (int j = 0; j < 6; j ++)
      {
        getchar(); scanf("%c", &letter); //printf("%c%c", letter, j < 6 - 1 ? ' ' : '\n');
        if (pool[j][crypt[letter - 'A'][0]] == n - 1)
          password[j] = crypt[letter - 'A'][0];
        if (pool[j][crypt[letter - 'A'][1]] == n - 1)
          password[j] = crypt[letter - 'A'][1];
        pool[j][crypt[letter - 'A'][0]] ++;
        pool[j][crypt[letter - 'A'][1]] ++;
      }
    }

    printf("Teste %d\n", ++ t);
    for (int j = 0; j < 6; j ++)
      printf("%d%c", password[j], j < 6 - 1 ? ' ' : '\n');
  }
  return(0);
}