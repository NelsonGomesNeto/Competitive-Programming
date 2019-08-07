#include <bits/stdc++.h>
#define lli long long int
int mat[3][(int) 1e7], n;

lli solve()
{
  lli ans = 0;
  int toFill = 0;
  for (int i = 0; i < 3; i ++)
    for (int j = 0; j < n; j ++)
      if (!mat[i][j])
      {
        toFill = 1;
      }
  if (!toFill) return(1);
}

int main()
{
  scanf("%d", &n);
  memset(mat, 0, sizeof(mat));
  lli ans = solve();
  return(0);
}
