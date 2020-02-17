#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

int n, m;
vector<vector<int>> mat;

int di[8] = {1, 1, 1, 0, 0, -1, -1, -1}, dj[8] = {1, 0, -1, 1, -1, 1, 0, -1};
int floodFill(int c, int i, int j)
{
  if (i < 0 || j < 0 || i >= n || j >= m || mat[i][j] != c) return false;
  mat[i][j] = -1;
  int sz = 1;
  for (int k = 0; k < 8; k ++)
    sz += floodFill(c, i + di[k], j + dj[k]);
  return sz;
}

int main()
{
  while (scanf("%d %d", &n, &m) != EOF)
  {
    mat.clear();
    mat.resize(n, vector<int>(m));
    for (int i = 0; i < n; i ++)
      for (int j = 0; j < m; j ++)
        scanf("%1d", &mat[i][j]);

    int groups = 0, biggest = 0;
    for (int i = 0; i < n; i ++)
      for (int j = 0; j < m; j ++)
        if (mat[i][j] != -1)
          groups ++, biggest = max(biggest, floodFill(mat[i][j], i, j));
    printf("%d %d\n", groups, biggest);
  }
  return 0;
}