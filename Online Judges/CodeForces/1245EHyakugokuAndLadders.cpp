#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 10; int n = 10;
const ldouble inf = 1e9;
int mat[maxN][maxN];

struct Pos
{
  int i, j;
  Pos operator+(const int k)
  {
    if (i & 1)
    {
      if (j + k < 10)
        return {i, j + k};
      return {i - 1, 10 - (k - (9 - j))};
    }
    else
    {
      if (j - k >= 0)
        return {i, j - k};
      return {i - 1, -(j - k + 1)};
    }
  }
};

ldouble memo[maxN][maxN][2], missing[7];
ldouble fillMissing(int m = 6, int it = 0)
{
  if (m == 0) return 0;
  if (it == 1000) return 0;
  if (missing[m] == -1)
  {
    ldouble ans = 1;
    for (int dice = 1; dice <= 6; dice ++)
      ans += fillMissing(dice > m ? m : m - dice, dice > m ? it + 1 : 0) / 6;
    missing[m] = ans;
  }
  return missing[m];
}
ldouble solve(Pos pos = {9, 0}, bool fromLadder = false)
{
  if (pos.i == 0 && pos.j == 0) return 0;
  if (pos.i == 0 && pos.j <= 6) return missing[pos.j];

  if (memo[pos.i][pos.j][fromLadder] == -1)
  {
    ldouble ans = 1;
    for (int dice = 1; dice <= 6; dice ++)
      ans += solve(pos + dice, false) / 6;
    if (mat[pos.i][pos.j] != 0 && !fromLadder)
      ans = min(ans, solve({pos.i - mat[pos.i][pos.j], pos.j}, true));
    memo[pos.i][pos.j][fromLadder] = ans;
  }
  return memo[pos.i][pos.j][fromLadder];
}

int main()
{
  for (int i = 1; i <= 6; i ++) missing[i] = -1;
  fillMissing();

  while (true)
  {
    bool ended = false;
    for (int i = 0; i < n; i ++)
      for (int j = 0; j < n; j ++)
        if (scanf("%d", &mat[i][j]) == EOF)
          ended = true;
    if (ended) break;

    for (int i = 0; i < n; i ++)
      for (int j = 0; j < n; j ++)
        memo[i][j][0] = memo[i][j][1] = -1;
    ldouble ans = solve();
    printf("%.15Lf\n", ans);
  }

  return 0;
}
