#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 16; int n, m, a, b;
int freePos = 0;
bool mat[maxN][maxN];

int solve(int i = 0, int j = 0, int aa = a, int bb = b)
{
  // if (i == n)
  //   return freePos == 0;
  if (freePos == 0)
    return 1;

  int ans = 0;
  if (!mat[i][j])
  {
    if (bb)
    {
      mat[i][j] = true, freePos--;
      ans += solve(i + (j == m - 1), (j + 1) % m, aa, bb - 1);
      mat[i][j] = false, freePos++;
    }

    if (aa)
    {
      if (j + 1 < m && !mat[i][j + 1])
      {
        mat[i][j] = true, freePos--;
        mat[i][j + 1] = true, freePos--;
        ans += solve(i + (j == m - 1), (j + 1) % m, aa - 1, bb);
        mat[i][j] = false, freePos++;
        mat[i][j + 1] = false, freePos++;
      }
      if (i + 1 < n && !mat[i + 1][j])
      {
        mat[i][j] = true, freePos--;
        mat[i + 1][j] = true, freePos--;
        ans += solve(i + (j == m - 1), (j + 1) % m, aa - 1, bb);
        mat[i][j] = false, freePos++;
        mat[i + 1][j] = false, freePos++;
      }
    }
  }
  else
    ans += solve(i + (j == m - 1), (j + 1) % m, aa, bb);

  return ans;
}

int main()
{
  while (~scanf("%d %d %d %d", &n, &m, &a, &b))
  {
    memset(mat, false, sizeof(mat)), freePos = n*m;
    int ans = solve();
    printf("%d\n", ans);
  }
  return 0;
}