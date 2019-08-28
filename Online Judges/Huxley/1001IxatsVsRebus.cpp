#include <bits/stdc++.h>
#define lli long long int
using namespace std;

const int maxN = 100; int n, m, k, h, b;
int di[5] = {1, -1, 1, -1, 0}, dj[5] = {1, -1, -1, 1, 0};
int mat[maxN][maxN], ships[maxN*maxN][3];

void printMatrix()
{
  memset(mat, 0, sizeof(mat));
  for (int i = 0; i < k; i ++)
    if (ships[i][2])
    {
      mat[ships[i][0]][ships[i][1]] = 1;
      // printf("%d %d\n", ships[i][0], ships[i][1]);
    }
  for (int i = 0; i < n; i ++)
    for (int j = 0; j < m; j ++)
      printf("%d%c", mat[i][j], j < m - 1 ? ' ' : '\n');
}

int fix(int i, int size)
{
  return ((i % size) + size) % size;
}
void killAt(int i, int j)
{
  for (int s = 0; s < k; s ++)
    if (ships[s][0] == i && ships[s][1] == j)
      ships[s][2] = false;
}
void explode(int i, int j)
{
  for (int d = 0; d < 5; d ++)
    killAt(fix(i + di[d], n), fix(j + dj[d], m));
}

void moveShips()
{
  for (int i = 0; i < k; i ++)
    if (ships[i][2])
      ships[i][0] = fix(ships[i][0] - 1, n), ships[i][1] = fix(ships[i][1] + 1, m);
}

int main()
{
  scanf("%d %d %d", &n, &m, &k);
  for (int i = 0; i < k; i ++)
  {
    int y, x; scanf("%d %d", &y, &x);
    mat[y][x] = 1, ships[i][0] = y, ships[i][1] = x, ships[i][2] = true;
  }
  printMatrix();

  scanf("%d %d", &h, &b);
  for (int i = 0; i < h; i ++)
  {
    printf("\n");
    for (int j = 0; j < b; j ++)
    {
      int y, x; scanf("%d %d", &y, &x);
      explode(y, x);
    }
    moveShips();
    printMatrix();
  }

  return(0);
}