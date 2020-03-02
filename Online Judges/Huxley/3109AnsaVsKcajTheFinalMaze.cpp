#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 100; int n, m;
int mat[maxN][maxN];
int di[4] = {1, -1, 0, 0}, dj[4] = {0, 0, 1, -1};

bool valid(int i, int j)
{
  return i >= 0 && j >= 0 && i < n && j < m && mat[i][j] != '#';
}

int main()
{
  scanf("%d %d", &n, &m);
  for (int i = 0; i < n; i ++)
    for (int j = 0; j < m; j ++)
      scanf("%d", &mat[i][j]);

  int q;
  while (scanf("%d", &q) != EOF)
  {
    string ans = "";
    ans += (char)mat[0][0];
    int i = 0, j = 0;
    while (q --)
    {
      int op; scanf("%d", &op);
      int ni = i + di[op], nj = j + dj[op];
      if (valid(ni, nj))
        i = ni, j = nj, ans += (char)mat[ni][nj];
    }
    printf("%s\n", ans.c_str());
  }
  return 0;
}