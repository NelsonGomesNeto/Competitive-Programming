#include <bits/stdc++.h>
using namespace std;
const int maxSize = 1e6, maxLog = floor(log2(1e6)) + 1;
int sparseTable[2][maxSize][maxLog + 1], logdp[maxSize + 1];

void fillLogDP()
{
  logdp[1] = 0;
  for (int i = 0; i <= maxSize; i ++) logdp[i] = logdp[i >> 1] + 1;
}

void build(int a[], int n, int logn)
{
  for (int i = 0; i < n; i ++) sparseTable[0][i][0] = sparseTable[1][i][0] = a[i];
  for (int j = 1; j <= logn; j ++)
    for (int i = 0, shift = (1 << (j - 1)); i < n; i ++)
    {
      sparseTable[0][i][j] = min(sparseTable[0][i][j - 1], sparseTable[0][i + shift][j - 1]);
      sparseTable[1][i][j] = max(sparseTable[1][i][j - 1], sparseTable[1][i + shift][j - 1]);
    }
}

int query(int lo, int hi, int kind)
{
  int ans = kind ? INT_MIN : INT_MAX;
  for (int j = maxLog; j >= 0; j --)
    if (lo + (1 << j) - 1 <= hi)
    {
      ans = kind ? max(ans, sparseTable[1][lo][j]) : min(ans, sparseTable[0][lo][j]);
      lo += 1 << j;
    }
  return(ans);
}

int main()
{
  int n; scanf("%d", &n);
  int b[n]; for (int i = 0; i < n; i ++) scanf("%d", &b[i]);
  build(b, n, floor(log2(n)) + 1); fillLogDP();

  int q, lo, hi; scanf("%d", &q);
  while (q --)
  {
    scanf("%d %d", &lo, &hi);
    int bigLeft = 0; if (lo) bigLeft = query(0, lo - 1, 1);
    int bigRight = 0; if (hi < n - 1) bigRight = query(hi + 1, n - 1, 1);
    int big = max(bigLeft, bigRight), bigRange = query(lo, hi, 1), small = query(lo, hi, 0);
    printf("%.1lf\n", max((double) big + small, small + (bigRange - small) / 2.0));
  }
  return(0);
}