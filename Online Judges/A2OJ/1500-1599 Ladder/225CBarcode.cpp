#include <bits/stdc++.h>
using namespace std;

const int maxN = 1e3, maxM = 1e3, inf = 1e8; int n, m, x, y;
char picture[maxN][maxM + 1];
struct Column
{
  int black, white;
  bool operator<(const Column &a) const { return(black < a.black); }
};
Column columns[maxM];

int memo[maxM][maxM][2];
int solve(int i = 0, int before = 0, bool black = 0)
{
  if (i == m) return(before >= x && before <= y ? 0 : inf);
  if (memo[i][before][black] == -1)
  {
    int ans = inf, change = black ? columns[i].black : columns[i].white, notChange = black ? columns[i].white : columns[i].black;
    if (before == y) ans = solve(i + 1, 1, !black) + change;
    if (i && before < x) ans = solve(i + 1, before + 1, black) + notChange;
    if (before >= x && before + 1 <= y) ans = min({ans, solve(i + 1, 1, !black) + change, solve(i + 1, before + 1, black) + notChange});
    if (i == 0) ans = min({ans, solve(i + 1, 1, true) + columns[i].white, solve(i + 1, 1, false) + columns[i].black});
    memo[i][before][black] = ans;
  }
  return(memo[i][before][black]); 
}

int main()
{
  scanf("%d %d %d %d", &n, &m, &x, &y);
  for (int i = 0; i < n; i ++) scanf(" %s", picture[i]);
  for (int j = 0; j < m; j ++)
    for (int i = 0; i < n; i ++)
      columns[j].black += picture[i][j] == '#',
      columns[j].white += picture[i][j] == '.';

  memset(memo, -1, sizeof(memo));
  int painted = solve();

  printf("%d\n", painted);

  return(0);
}