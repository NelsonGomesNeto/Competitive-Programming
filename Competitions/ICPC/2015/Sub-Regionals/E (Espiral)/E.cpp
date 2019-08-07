#include <bits/stdc++.h>
#define lli long long int
using namespace std;

/* Tutorial:
  4n - 4, (2, 1)
  4n - 4 + 4n - 12, (3, 2)
  4n - 4 + 4n - 12 + 4n - 20, (4, 3)
  ... (It's an AP where a1 = 4n - 4, q = -8)
  So, just do a binary seach to find the starting position
*/
lli n, b;

lli apSum(lli a1, lli q, lli nn)
{
  // printf("\ta1: %lld, an: %lld | %lld\n", a1, a1 + (nn - 1LL)*q, nn);
  // return(n * (a1 + (a1 + (n - 1)*q)) / 2);
  return(nn * (2LL*a1 + (nn - 1LL)*q) / 2);
}

lli binarySearch(lli target, lli lo = 1, lli hi = n >> 1)
{
  while (lo < hi)
  {
    lli mid = ((lo + hi) >> 1) + ((lo + hi) & 1);
    // printf("%lld %lld\n", mid, apSum(4*n - 4, -8, mid));
    if (target >= apSum(4*n - 4, -8, mid)) lo = mid;
    else hi = mid - 1;
  }
  return(lo);
}

lli di[4] = {0, 1, 0, -1}, dj[4] = {1, 0, -1, 0};

int main()
{
  scanf("%lld %lld", &n, &b);
  if (n == 1) { printf("1 1\n"); return(0); }

  lli i = 1, j = 1, num = 1, pos = 0;
  lli dir[4] = {n - 1, n - 1, n - 1, n - 2};
  if (b > 4*n - 4)
  {
    pos = binarySearch(b);
    num = apSum(4*n - 4, -8, pos);
    i = pos + 1, j = pos;
    lli aux[4] = {n - 2 - (pos - 1)*2, n - 3 - (pos - 1)*2, n - 3 - (pos - 1)*2, n - 4 - (pos - 1)*2};
    memcpy(dir, aux, sizeof(dir));
  }
  // printf("%lld %lld | %lld\n", i, j, num);
  // printf("%lld %lld %lld %lld\n", dir[0], dir[1], dir[2], dir[3]);
  int k;
  for (k = 0; k < 4 && num + dir[k] < b; k ++)
  {
    i += di[k] * dir[k], j += dj[k] * dir[k];
    num += dir[k];
    // printf("%lld %lld | %lld\n", i, j, num);
  }
  if (num < b)
  {
    i += di[k] * (b - num), j += dj[k] * (b - num);
    num = 0;
  }
  printf("%lld %lld\n", i, j);

  return(0);
}
/*
  lli mat[n + 2][n + 2]; memset(mat, 0, sizeof(mat));
  for (int i = 0; i < n + 2; i ++) mat[i][0] = mat[0][i] = mat[n + 1][i] = mat[i][n + 1] = -1;

  int k = 0, i = 1, j = 1; lli num = 1;
  while (mat[i][j] == 0)
  {
    for (; mat[i][j] == 0; i += di[k], j += dj[k])
      mat[i][j] = num ++;
    i -= di[k], j -= dj[k];
    k = (k + 1) % 4;
    i += di[k], j += dj[k];
  }

  for (int i = 1; i <= n; i ++)
    for (int j = 1; j <= n; j ++)
      printf("%4lld%c", mat[i][j], j < n ? ' ' : '\n');

  lli prv = (4*n - 5 + 1);
  for (int i = 0; i < 10; i ++)
  {
    printf("%lld -- %lld | (%d, %d)\n", prv, apSum(4*n - 4, -8, i + 1), i + 1, i + 1);
    prv += 4*n - 12 - 8*i;
  }
*/