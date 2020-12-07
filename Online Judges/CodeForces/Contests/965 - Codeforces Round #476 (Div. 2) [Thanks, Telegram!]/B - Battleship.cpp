#include <bits/stdc++.h>
#define DEBUG if(0)
char field[100][101]; int f[4][100][100];

int count(int spaces, int k)
{
  if (spaces / k)
    return(1 + spaces - k);
  return(0);
}

int main()
{
  int n, k; scanf("%d %d", &n, &k);
  for (int i = 0; i < n; i ++)
    scanf("\n%s", field[i]);

  for (int i = 0; i < n; i ++)
  {
    int left = 0, right = 0, up = 0, down = 0;
    for (int j = 0, l = n - 1; j < n; j ++, l --)
    {
      if (field[i][j] == '#') left = 0;
      else left += (left < k);
      if (field[i][l] == '#') right = 0;
      else right += (right < k);
      if (field[j][i] == '#') up = 0;
      else up += (up < k);
      if (field[l][i] == '#') down = 0;
      else down += (down < k);
      f[0][i][j] = left; f[1][i][l] = right;
      f[2][j][i] = up; f[3][l][i] = down;
    }
  }

  int bi = 0, bj = 0, b = 0;
  for (int i = 0; i < n; i ++)
    for (int j = 0; j < n; j ++)
    {
      int now = count(f[0][i][j] + f[1][i][j] - 1, k) + count(f[2][i][j] + f[3][i][j] - 1, k);
      DEBUG printf("(%d, %d): %d %d %d %d = %d\n", i, j, f[0][i][j], f[1][i][j], f[2][i][j], f[3][i][j], now);
      if (now > b)
      {
        b = now; bi = i; bj = j;
      }
    }

  printf("%d %d\n", bi + 1, bj + 1);

  return(0);
}
