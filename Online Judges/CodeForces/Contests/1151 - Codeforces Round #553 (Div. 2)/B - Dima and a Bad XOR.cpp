#include <bits/stdc++.h>
using namespace std;

const int maxN = 500, maxM = 500, maxA = 1023; int n, m;
int mat[maxN][maxM], chosen[maxN];

int memo[maxN][maxA + 1];
int solve(int i, int value)
{
  if (i == n) return(value);
  if (memo[i][value] == -1)
  {
    int ans = 0;
    for (int j = 0; j < m && ans == 0; j ++)
    {
      ans = max(ans, solve(i + 1, value ^ mat[i][j]));
      if (ans) chosen[i] = j;
    }
    memo[i][value] = ans;
  }
  return(memo[i][value]);
}

int main()
{
  scanf("%d %d", &n, &m);
  for (int i = 0; i < n; i ++)
    for (int j = 0; j < m; j ++)
      scanf("%d", &mat[i][j]);

  memset(memo, -1, sizeof(memo));
  int ans = solve(0, 0);
  if (ans == 0)
    printf("NIE\n");
  else
  {
    printf("TAK\n");
    for (int i = 0; i < n; i ++) printf("%d ", chosen[i] + 1);
    printf("\n");
  }

  return(0);
}