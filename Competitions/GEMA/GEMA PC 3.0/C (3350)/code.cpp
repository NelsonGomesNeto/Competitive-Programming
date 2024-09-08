#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 50, maxC = 10; int n, m, c;
char mat[maxN][maxN + 1], colors[maxC + 1];
struct Pos
{
  int i, j;
  Pos operator+(const Pos &other)
  {
    return Pos{i + other.i, j + other.j};
  }
  bool operator==(const Pos &other) const
  {
    return i == other.i && j == other.j;
  }
  bool valid(char color)
  {
    return i >= 0 && i < n && j >= 0 && j < m && (mat[i][j] == '.' || mat[i][j] == color);
  }
};
Pos origin[maxC], destination[maxC];
int di[4] = {0, 0, -1, 1}, dj[4] = {1, -1, 0, 0};
// char dir[5] = "><^v";
char dir[5] = "--||";

bool allFilled()
{
  for (int i = 0; i < n; i++)
    for (int j = 0; j < m; j++)
      if (mat[i][j] == '.')
        return false;
  return true;
}
bool solve(int i);
bool solve2(int i, char color, Pos u, Pos dest)
{
  if (!u.valid(color)) return false;
  if (u == dest) return solve(i + 1);

  char prv = mat[u.i][u.j];
  for (int k = 0; k < 4; k++)
  {
    mat[u.i][u.j] = dir[k];
    if (solve2(i, color, u + Pos{di[k], dj[k]}, dest))
    {
      if (prv != color) mat[u.i][u.j] = dir[k];
      else mat[u.i][u.j] = prv;
      return true;
    }
  }
  mat[u.i][u.j] = prv;
  return false;
}
bool solve(int i = 0)
{
  if (i == c) return allFilled();
  return solve2(i, colors[i], origin[i], destination[i]);
}

int main()
{
  int t;
  while (scanf("%d", &t) != EOF)
    for (int tt = 1; tt <= t; tt++)
    {
      scanf("%d %d %d", &n, &m, &c);
      scanf(" %s", colors);
      for (int i = 0; i < n; i++)
        scanf(" %s", mat[i]);
      for (int cc = 0; cc < c; cc++)
      {
        bool foundOrigin = false;
        for (int i = 0; i < n; i++)
          for (int j = 0; j < m; j++)
            if (mat[i][j] == colors[cc])
            {
              if (foundOrigin) destination[cc] = Pos{i, j};
              else origin[cc] = Pos{i, j};
              foundOrigin = true;
            }
      }

      bool can = solve();
      printf("%s\n", can ? "Yes" : "No");
      // if (can)
      //   for (int i = 0; i < n; i++)
      //     printf("%s\n", mat[i]);
    }
  return 0;
}