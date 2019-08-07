#include <bits/stdc++.h>
#define DEBUG if(0)
using namespace std;

int main()
{
  int n, m; scanf("%d %d", &n, &m);
  char table[n][m + 1];
  for (int i = 0; i < n; i ++) scanf("\n%s", table[i]);

  set<pair<int, int> > center;
  int hor[n][m], ver[n][m]; memset(hor, 0, sizeof(hor)); memset(ver, 0, sizeof(ver));

  for (int i = 0; i < n; i ++)
    for (int j = 0, start; j < m; j ++)
      if (table[i][j] == '*')
      {
        start = j;
        while (j < m && table[i][j] == '*') j ++;
        if (j - start < 3) continue;
        int mid = (j + start) / 2, size = j - start, diff = 0;
        while (size > 0)
        {
          if (mid + diff < m) hor[i][mid + diff] = size + !(size & 1);
          if (mid - diff >= 0) hor[i][mid - diff] = size + !(size & 1);
          diff ++;
          size -= 2;
        }
        center.insert({i, start + (j - start) / 2});
      }

  for (int j = 0; j < m; j ++)
    for (int i = 0, start; i < n; i ++)
      if (table[i][j] == '*')
      {
        start = i;
        while (i < n && table[i][j] == '*') i ++;
        if (i - start < 3) continue;
        int mid = (i + start) / 2, size = i - start, diff = 0;
        while (size > 0)
        {
          if (mid + diff < n) ver[mid + diff][j] = size + !(size & 1);
          if (mid - diff >= 0) ver[mid - diff][j] = size + !(size & 1);
          diff ++;
          size -= 2;
        }
        center.insert({start + (i - start) / 2, j});
      }

  int stars = 0;
  for (auto c: center)
  {
    DEBUG printf("%d %d -- %d %d\n", c.first, c.second, hor[c.first][c.second], ver[c.first][c.second]);
    int mini = min(hor[c.first][c.second], ver[c.first][c.second]) / 2;
    if (mini)
    {
      for (int diff = 0, i = c.first, j = c.second; diff <= mini; diff ++)
      {
        if (i + diff < n) table[i + diff][j] = '.';
        if (i - diff >= 0) table[i - diff][j] = '.';
        if (j + diff < m) table[i][j + diff] = '.';
        if (j - diff >= 0) table[i][j - diff] = '.';
      }
      stars ++;
    }
  }

  for (int i = 0; i < n; i ++) for (int j = 0; j < m; j ++)
    if (table[i][j] == '*')
    {
      printf("-1\n");
      return(0);
    }

  printf("%d\n", stars);
  for (auto c: center)
    if (min(hor[c.first][c.second], ver[c.first][c.second]) / 2)
      printf("%d %d %d\n", c.first + 1, c.second + 1, min(hor[c.first][c.second], ver[c.first][c.second]) / 2);

  return(0);
}