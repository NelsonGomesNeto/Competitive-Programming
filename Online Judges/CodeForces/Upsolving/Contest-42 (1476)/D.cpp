#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 3e5 + 1; int n;
char s[maxN + 1];


int memo[maxN][2][2];
int solve(int i, int di, bool turn)
{
  int &ans = memo[i][di == 1][turn];
  if (ans != -1) return ans;

  ans = 1;
  if ((di == -1 && i - 1 >= 0 && s[i - 1] == (turn ? 'R' : 'L'))
    || (di == 1 && i + 1 <= n && s[i] == (turn ? 'L' : 'R')))
    ans += solve(i + di, di, !turn);

  return ans;
}

int main()
{
  int t; scanf("%d", &t);
  for (int tt = 1; tt <= t; tt++)
  {
    scanf("%d", &n);
    scanf(" %s", s);

    for (int i = 0; i <= n; i++)
      for (int j = 0; j < 2; j++)
        for (int k = 0; k < 2; k++)
          memo[i][j][k] = -1;
    for (int di = -1; di <= 1; di += 2)
      for (int i = 0; i <= n; i++)
        solve(i, di, false);

    DEBUG
    {
      printf("\tleft : ");
      for (int i = 0; i <= n; i++)
        printf("%d%c", memo[i][0][false], i < n ? ' ' : '\n');
      printf("\tright: ");
      for (int i = 0; i <= n; i++)
        printf("%d%c", memo[i][1][false], i < n ? ' ' : '\n');
    }

    for (int i = 0; i <= n; i++)
      printf("%d%c", memo[i][0][false] + memo[i][1][false] - 1, i < n ? ' ' : '\n');
  }
  return 0;
}
