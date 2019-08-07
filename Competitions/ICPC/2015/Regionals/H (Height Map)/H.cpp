#include <bits/stdc++.h>
using namespace std;

const int maxN = 100; int r, c;
int v[maxN][maxN];
bool visited[maxN][maxN];

int di[4] = {0, 0, 1, -1}, dj[4] = {1, -1, 0, 0};
void floodfill(int i, int j, int h)
{
  if (i < 0 || j < 0 || i >= r || j >= c || visited[i][j] || v[i][j] != h) return;
  visited[i][j] = true;
  for (int k = 0; k < 4; k ++) floodfill(i + di[k], j + dj[k], h);
}

int main()
{
  while (scanf("%d %d", &r, &c) != EOF)
  {
    memset(visited, false, sizeof(visited));
    for (int i = 0; i < r; i ++)
      for (int j = 0; j < c; j ++)
        scanf("%d", &v[i][j]);
    // for (int i = 0; i < r; i ++)
    //   for (int j = 0; j < c; j ++)
    //     printf("%5d%c", v[i][j], j < c - 1 ? ' ' : '\n');

    int ans = 5;
    for (int i = 0; i < r; i ++)
      for (int j = 0; j < c; j ++)
        if (!visited[i][j])
        {
          floodfill(i, j, v[i][j]);
          ans ++;
        }
    for (int i = 1; i < r; i ++)
      for (int j = 0; j < c; j ++)
        if (v[i][j] > v[i - 1][j])
        {
          while (j < c - 1 && v[i - 1][j] < v[i][j + 1] && v[i - 1][j + 1] < v[i][j + 1] && v[i - 1][j + 1] < v[i][j])
            j ++;
          ans ++;
        }
    for (int i = r - 2; i >= 0; i --)
      for (int j = 0; j < c; j ++)
        if (v[i][j] > v[i + 1][j])
        {
          while (j < c - 1 && v[i + 1][j] < v[i][j + 1] && v[i + 1][j + 1] < v[i][j + 1] && v[i + 1][j + 1] < v[i][j])
            j ++;
          ans ++;
        }
    for (int j = 1; j < c; j ++)
      for (int i = 0; i < r; i ++)
        if (v[i][j] > v[i][j - 1])
        {
          while (i < r - 1 && v[i][j - 1] < v[i + 1][j] && v[i + 1][j - 1] < v[i + 1][j] && v[i + 1][j - 1] < v[i][j])
            i ++;
          ans ++;
        }
    for (int j = c - 2; j >= 0; j --)
      for (int i = 0; i < r; i ++)
        if (v[i][j] > v[i][j + 1])
        {
          while (i < r - 1 && v[i][j + 1] < v[i + 1][j] && v[i + 1][j + 1] < v[i + 1][j] && v[i + 1][j + 1] < v[i][j])
            i ++;
          ans ++;
        }
    printf("%d\n", ans);
  }

  return(0);
}