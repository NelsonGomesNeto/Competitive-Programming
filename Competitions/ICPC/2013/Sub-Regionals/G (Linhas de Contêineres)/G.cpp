#include <bits/stdc++.h>
#define lli long long int
using namespace std;

const int maxN = 300, inf = 1e9; int L, C;
int mat[maxN][maxN];

void swapLines(int i, int j)
{
  for (int k = 0; k < C; k ++) swap(mat[i][k], mat[j][k]);
}
void swapColumns(int i, int j)
{
  for (int k = 0; k < L; k ++) swap(mat[k][i], mat[k][j]);
}

int solve()
{
  int ans = 0;
  for (int k = 0; k < L; k ++)
    for (int i = 0; i < L; i ++)
      if (i != mat[i][0] / C)
        swapLines(i, mat[i][0] / C), ans ++;
  for (int k = 0; k < C; k ++)
    for (int i = 0; i < C; i ++)
    {
      if (mat[0][i] >= C) return(inf);
      if (i != mat[0][i])
        swapColumns(i, mat[0][i]), ans ++;
    }
  return(ans);
}

int main()
{
  while (scanf("%d %d", &L, &C) != EOF)
  {
    for (int i = 0; i < L; i ++)
      for (int j = 0; j < C; j ++)
      {
        scanf("%d", &mat[i][j]);
        mat[i][j] --;
      }

    int ans = solve();
    bool can = ans < inf;
    for (int i = 0; i < L; i ++)
      for (int j = 0; j < C; j ++)
        if (mat[i][j] != i*C + j)
          can = false;
    if (!can) printf("*\n");
    else printf("%d\n", ans);
  }
  return(0);
}