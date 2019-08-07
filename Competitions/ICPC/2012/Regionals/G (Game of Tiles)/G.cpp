#include <bits/stdc++.h>
#define lli long long int
using namespace std;

const int maxR = 50; int r, c;
char mat[maxR][maxR + 1], matCopy[maxR][maxR + 1];
int di[4] = {1, -1, 0, 0}, dj[4] = {0, 0, 1, -1};

bool invalid(int i, int j)
{
  return(i < 0 || j < 0 || i >= r || j >= c || mat[i][j] != '.');
}
bool winningState(int i, int j)
{
  for (int k = 0; k < 4; k ++)
    if (!invalid(i + di[k], j + dj[k]))
      return(false);
  return(true);
}

int solve(int i, int j, bool first = true)
{
  for (int k = 0; k < 4; k ++)
  {
    int ni = i + di[k], nj = j + dj[k];
    if (invalid(ni, nj)) continue;
    mat[i][j] = first ? '1' : '2';
    int ans = solve(ni, nj, !first);
    mat[i][j] = '.';
    if (ans == (first ? 2 : 1)) return(first ? 2 : 1);
  }
  return(first ? 1 : 2);
}

int main()
{
  int t = 1;
  while (scanf("%d %d", &r, &c) != EOF)
  {
    for (int i = 0; i < r; i ++)
      scanf(" %s", mat[i]);
    printf("Input: %d\n", t ++);
    for (int i = 0; i < r; i ++)
      printf("%s\n", mat[i]);
    memcpy(matCopy, mat, sizeof(mat));

    int won = 2;
    for (int i = 0; i < r && won == 2; i ++)
      for (int j = 0; j < c && won == 2; j ++)
        if (mat[i][j] == '.')
        {
          won = solve(i, j);
          if (won == 1)
          {
            printf("won starting at: %d %d\n", i, j);
            for (int i = 0; i < r; i ++)
              printf("%s\n", mat[i]);
          }
          else
          {
            // printf("Lost\n");
            memcpy(mat, matCopy, sizeof(mat));
          }
        }
    printf("%d\n", won);
  }
  return(0);
}