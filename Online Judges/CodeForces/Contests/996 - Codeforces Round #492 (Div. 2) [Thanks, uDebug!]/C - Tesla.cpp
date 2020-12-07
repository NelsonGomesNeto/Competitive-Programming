#include <bits/stdc++.h>
int pl[4][50];

int park(int ci, int cj, int li, int lj, int now)
{
  deque<vector<int> > queue; queue.push_back({ci, cj, now});
  while ()
}

int main()
{
  int n, k; scanf("%d %d", &n, &k);
  pair<int, int> car[k + 1];
  pair<int, int> lot[k + 1];
  for (int i = 0; i < 4; i ++)
    for (int j = 0; j < n; j ++)
    {
      scanf("%d", &pl[i][j]);
      if (i > 0 && i < 3 && pl[i][j]) car[pl[i][j]] = {i, j};
      if ((i == 0 || i == 3) && pl[i][j]) lot[pl[i][j]] = {i, j};
    }

  int movements = 0;
  for (int i = 1; i <= k; i ++)
  {
    movements = park(car[i].first, car[i].second, lot[i].first, lot[i].second, movements);
  }

  printf("%d\n", movements);
  return(0);
}