#include <bits/stdc++.h>
char field[15][15 + 1];
int queen[15][2];

int nqueens(int x, int n)
{
  if (x == n) return(1);

  int total = 0, valid = 0;
  for (int y = 0; y < n; y ++)
  {
    valid = field[x][y] != '*';
    for (int i = 0; i < x && valid; i ++)
      if (queen[i][1] == y || abs(queen[i][0] - x) == abs(queen[i][1] - y))
        valid = 0;

    if (valid)
    {
      queen[x][0] = x; queen[x][1] = y;
      total += nqueens(x + 1, n);
    }
  }

  return(total);
}

int main()
{
  int n, run = 1;
  while (scanf("%d", &n) && n > 0)
  {
    for (int i = 0; i < n; i ++)
      scanf("\n%s", field[i]);

    int ans = nqueens(0, n);
    printf("Case %d: %d\n", run ++, ans);
  }

  return(0);
}