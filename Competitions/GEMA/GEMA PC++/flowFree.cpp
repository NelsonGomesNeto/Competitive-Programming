#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 4;
char mat[maxN][maxN + 1];
int di[4] = {0, 0, -1, 1}, dj[4] = {1, -1, 0, 0};

bool solve();

bool dfs(int i, int j, char color, bool start)
{
  if (i < 0 || j < 0 || i >= 4 || j >= 4 || (mat[i][j] != 'W' && mat[i][j] != color))
    return false;
  char prv = mat[i][j];
  if (mat[i][j] == color && !start)
  {
    mat[i][j] = tolower(color);
    if (solve()) return true;
  }
  mat[i][j] = tolower(color);
  for (int k = 0; k < 4; k ++)
    if (dfs(i + di[k], j + dj[k], color, false))
      return true;
  mat[i][j] = prv;
  return false;
}

bool solve()
{
  bool solved = true;
  for (int i = 0; i < 4; i ++)
    for (int j = 0; j < 4; j ++)
    {
      if (mat[i][j] >= 'A' && mat[i][j] <= 'Z') solved = false;
      if (mat[i][j] != 'W' && mat[i][j] >= 'A' && mat[i][j] <= 'Z')
        if (dfs(i, j, mat[i][j], true))
          return true;
    }
  return solved;
}

int main()
{
  for (int i = 0; i < 4; i ++)
    scanf("%s", mat[i]);

  printf("%s\n", solve() ? "solvable" : "not solvable");

  return 0;
}