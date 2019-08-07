#include <bits/stdc++.h>
#define DEBUG if(0)
using namespace std;

const int maxN = 100, maxM = 100; int n, m;

int main()
{
  scanf("%d %d", &n, &m);

  char t[n][m + 1], table[m][n + 1];
  for (int i = 0; i < n; i ++) scanf(" %s", t[i]);

  for (int j = 0; j < m; j ++)
    for (int i = 0; i < n; i ++)
      table[j][i] = t[i][j];

  bool toRemove[m]; memset(toRemove, false, sizeof(toRemove));
  bool tied[n]; for (int i = 0; i < n; i ++) tied[i] = true;
  for (int i = 0; i < m; i ++)
  {
    for (int j = 1; j < n; j ++)
    {
      if (!tied[j]) continue;
      if (table[i][j - 1] > table[i][j]) toRemove[i] = true;
    }
    if (toRemove[i]) continue;
    for (int j = 1; j < n; j ++)
    {
      if (!tied[j]) continue;
      tied[j] = table[i][j - 1] == table[i][j];
    }
  }

  int minRemovals = 0; for (int i = 0; i < m; i ++) minRemovals += toRemove[i];
  memset(t, '\0', sizeof(t));
  for (int i = 0, ii = 0; i < m; i ++)
  {
    if (toRemove[i]) continue;
    for (int j = 0; j < n; j ++) t[j][ii] = table[i][j];
    ii ++;
  }
  DEBUG for (int i = 0; i < n; i ++) printf("%s\n", t[i]);

  printf("%d\n", minRemovals);

  return(0);
}