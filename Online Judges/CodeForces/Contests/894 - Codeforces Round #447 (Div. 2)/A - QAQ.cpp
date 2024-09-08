#include <bits/stdc++.h>
using namespace std;

int dp[101][3][2];
char word[110], aux;

int findAll(int i, int now, int size, int done)
{
  if (now == 0 && done) return(1);
  if (i == size && !now && done) return(1);
  if (i == size) return(0);

  if (dp[i][now][done] == -1)
  {
    int ans = findAll(i + 1, now, size, done);

    if (now == 0 && word[i] == 'Q')
      ans += findAll(i + 1, 1, size, 1);
    if (now == 1 && word[i] == 'A')
      ans += findAll(i + 1, 2, size, 1);
    if (now == 2 && word[i] == 'Q')
      ans += findAll(i + 1, 0, size, 1);

    dp[i][now][done] = ans;
  }

  return(dp[i][now][done]);
}

int main()
{
  memset(dp, -1, sizeof(dp));
  int size = 0, q = 0;
  while (scanf("%c", &aux) != EOF && aux != '\n')
  {
    q += aux == 'Q';
    if (!q) continue;
    if (aux == 'Q' || aux == 'A')
      word[size ++] = aux;
  }

  //printf("%s\n", word);
  int ans = findAll(0, 0, size, 0);

  printf("%d\n", ans);

  return(0);
}


//
// char word[110], end;
//
// int main()
// {
//   int size = 0, acc[2][110], q = 0, a = 0;
//   while (scanf("%c", &end) != EOF && end != '\n')
//     word[size ++] = end;
//
//   int newSize = 0;
//   for (int i = 0; i < size; i ++)
//   {
//     if (word[i] != 'Q' && word[i] != 'A') continue;
//     if (word[i] == 'Q') q ++;
//     if (word[i] == 'A') a ++;
//     if (!q) continue;
//     acc[0][newSize ++] = q;
//     acc[1][newSize ++] = a;
//     printf("%d %d\n", q, a);
//   }
//
//   return(0);
// }