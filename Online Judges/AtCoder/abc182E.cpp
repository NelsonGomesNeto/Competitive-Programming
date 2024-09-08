#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxH = 1500, maxN = 5e5, maxM = 1e5; int h, w, n, m;
struct Pos
{
  int i, j;
  void read() { scanf("%d %d", &i, &j); i--, j--; }
};
Pos bulbs[maxN], blocks[maxM];
char mat[maxH][maxH + 1];
int lit[maxH][maxH];

// vector<int> rows[maxH], columns[maxH];
// int horizontalIn[maxH][maxH], horizontalOut[maxH][maxH];
// int verticalIn[maxH][maxH], verticalOut[maxH][maxH];

int main()
{
  while (scanf("%d %d %d %d", &h, &w, &n, &m) != EOF)
  {
    memset(mat, '.', sizeof(mat));
    // memset(horizontalIn, 0, sizeof(horizontalIn)), memset(horizontalOut, 0, sizeof(horizontalOut));
    // memset(verticalIn, 0, sizeof(verticalIn)), memset(verticalOut, 0, sizeof(verticalOut));
    memset(lit, 0, sizeof(lit));
    for (int i = 0; i < h; i++) mat[i][w] = '\0';

    for (int i = 0; i < n; i++)
    {
      bulbs[i].read();
      mat[bulbs[i].i][bulbs[i].j] = '@';
    }
    for (int i = 0; i < m; i++)
    {
      blocks[i].read();
      mat[blocks[i].i][blocks[i].j] = '#';
    }

    DEBUG
      for (int i = 0; i < h; i++)
        printf("%s\n", mat[i]);

    for (int i = 0; i < h; i++)
    {
      bool light = false;
      for (int j = 0; j < w; j++)
      {
        if (mat[i][j] == '#')
          light = false;
        if (mat[i][j] == '@')
          light = true;

        if (light)
          lit[i][j] = 1;
      }
      light = false;
      for (int j = w - 1; j >= 0; j--)
      {
        if (mat[i][j] == '#')
          light = false;
        if (mat[i][j] == '@')
          light = true;

        if (light)
          lit[i][j] = 1;
      }
    }

    for (int j = 0; j < w; j++)
    {
      bool light = false;
      for (int i = 0; i < h; i++)
      {
        if (mat[i][j] == '#')
          light = false;
        if (mat[i][j] == '@')
          light = true;

        if (light)
          lit[i][j] = 1;
      }
      light = false;
      for (int i = h - 1; i >= 0; i--)
      {
        if (mat[i][j] == '#')
          light = false;
        if (mat[i][j] == '@')
          light = true;

        if (light)
          lit[i][j] = 1;
      }
    }

    int ans = 0;
    for (int i = 0; i < h; i++)
      for (int j = 0; j < w; j++)
        ans += lit[i][j];
    printf("%d\n", ans);
  }
  return 0;
}