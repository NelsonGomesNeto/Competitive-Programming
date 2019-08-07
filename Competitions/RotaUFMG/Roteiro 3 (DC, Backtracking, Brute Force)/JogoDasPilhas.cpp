#include <bits/stdc++.h>
int dp[100][100][100], n;

bool isBitSet(int bit, int shift)
{
  return(bit & (1 << shift));
}

int calc(int pile[][3], int p, int at, int bit)
{
  return(p < n ? pile[p][at] * isBitSet(bit, at) : 0);
}

int canWin(int pile[][3], int i, int j, int k)
{
  //printf("%d %d %d\n", i, j, k);
  if (i == n && j == n && k == n) return(1);
  if (i > n || j > n || k > n) return(0);

  if (!dp[i][j][k])
  {
    dp[i][j][k] = 1;
    for (int bit = 1; bit < 8; bit ++)
      if (!((calc(pile, i, 0, bit) + calc(pile, j, 1, bit) + calc(pile, k, 2, bit)) % 3) && canWin(pile, i + isBitSet(bit, 0), j + isBitSet(bit, 1), k + isBitSet(bit, 2)))
        return(1);
  }
  return(0);
}

int main()
{
  while (scanf("%d", &n) && n)
  {
    memset(dp, 0, sizeof(dp));
    int pile[n][3], total = 0, every = 1;
    for (int i = 0; i < n; i ++)
      for (int j = 0, now = 0; j < 3; j ++)
      {
        scanf("%d", &pile[i][j]);
        now += pile[i][j];
        if (j == 2 && now % 3)
          every = 0;
        total += pile[i][j];
      }

    total = !(total % 3);
    if (total)
      total = canWin(pile, 0, 0, 0);
    printf("%d\n", total);
  }
  return(0);
}