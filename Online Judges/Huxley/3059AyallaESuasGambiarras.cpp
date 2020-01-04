#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 100; int n, b;
int mat[maxN][maxN];

bool valid(int i, int j, int k)
{
  if (j + (b >> 1) >= n || j - (b >> 1) < 0) return false;
  if (i - (b >> 1) < 0) return false;
  for (int ii = i, lv = 0; ii >= i - (b >> 1); ii --, lv ++)
    for (int jj = j - (b >> 1) + lv; jj <= j + (b >> 1) - lv; jj ++)
      if (mat[ii][jj] != k)
        return false;
  return true;
}

int solve(int k)
{
  int cnt = 0;
  for (int i = 0; i < n; i ++)
    for (int j = 0; j < n; j ++)
      cnt += valid(i, j, k);
  return cnt;
}

int main()
{
  int t; scanf("%d", &t);
  for (int tt = 1; tt <= t; tt ++)
  {
    scanf("%d %d", &b, &n);
    for (int i = 0; i < n; i ++)
      for (int j = 0; j < n; j ++)
        scanf("%d", &mat[i][j]);

    int one = solve(1), zero = solve(0);
    printf("Caso %d:\n", tt);
    printf("%d triangulos formados por 1\n", one);
    printf("%d triangulos formados por 0\n", zero);
  }
  return 0;
}