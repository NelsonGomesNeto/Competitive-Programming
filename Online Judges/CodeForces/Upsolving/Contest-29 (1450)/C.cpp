#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 3e2; int n;
char mat[maxN][maxN + 1];

int di[4] = {-1, 1, 0, 0}, dj[4] = {0, 0, -1, 1};
double countWins(int i, int j, bool flip)
{
  double wins = 0;
  for (int d = 0; d < 4; d++)
  {
    bool is = true;
    for (int t = 0; t < 3; t++)
    {
      int ni = i + t*di[d], nj = j + t*dj[d];
      if (ni < 0 || nj < 0 || ni >= n || nj >= n || mat[i][j] != mat[ni][nj])
        is = false;
    }
    wins += is ? 1 : 0;
    DEBUG if (is) printf("\t\t%d %d | %d\n", i, j, d);

    // if (d & 1)
    // {
    //   is = true;
    //   for (int t = -1; t <= 1; t++)
    //   {
    //     int ni = i + t*di[d], nj = j + t*dj[d];
    //     if (ni < 0 || nj < 0 || ni >= n || nj >= n || mat[i][j] != mat[ni][nj])
    //       is = false;
    //   }
    //   wins += is ? 1.1 : 0;
    // }
  }
  if (flip)
  {
    mat[i][j] = mat[i][j] == 'O' ? 'X' : 'O';
    wins -= countWins(i, j, false);
    mat[i][j] = mat[i][j] == 'O' ? 'X' : 'O';
  }
  return wins;
}

int main()
{
  int t; scanf("%d", &t);
  for (int tt = 1; tt <= t; tt++)
  {
    scanf("%d", &n);
    int k = 0;
    for (int i = 0; i < n; i++)
    {
      scanf(" %s", mat[i]);
      for (int j = 0; j < n; j++)
        if (mat[i][j] != '.')
          k++;
    }

    int done = 0;
    for (int p = 0; p < 2; p++)
    {
      priority_queue<pair<pair<double, int>, pair<int, int>>> pq;
      for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
          if (mat[i][j] != '.')
            pq.push({{countWins(i, j, true), false}, {i, j}});
      if (pq.empty() || pq.top().first.first <= 0)
        break;

      while (!pq.empty() && done <= k / 3)
      {
        int i = pq.top().second.first, j = pq.top().second.second;
        double w = pq.top().first.first; int redone = pq.top().first.second;
        pq.pop();

        if (countWins(i, j, true) != w)
          pq.push({{countWins(i, j, true), redone}, {i, j}});
        else if (p ? w : w > 0)
        {
          DEBUG printf("---------\n");
          DEBUG printf("%d %d - %lf - %lf\n", i, j, w, countWins(i, j, true));
          mat[i][j] = mat[i][j] == 'O' ? 'X' : 'O', done++;
          DEBUG {
            for (int i = 0; i < n; i++)
              printf("%s\n", mat[i]);
            fflush(stdout);
          }
        }
      }
    }

    assert(done <= k / 3);

    for (int i = 0; i < n; i++)
      printf("%s\n", mat[i]);
  }
  return 0;
}
