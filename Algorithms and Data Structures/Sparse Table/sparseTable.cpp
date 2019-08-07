#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
using namespace std;
const int maxSize = 1e6, maxLog = (int) floor(log2(1e6)) + 1;
lli sparseTable[maxSize][maxLog + 1], logdp[maxSize + 1];
lli zero = LLONG_MAX; // needs to change this depending on f function

void printArray(lli a[], int n)
{
  for (int i = 0; i < n; i ++) printf("%lld%c", a[i], i < n - 1 ? ' ' : '\n');
}

lli f(lli a, lli b)
{
  return(min(a, b));
}

void build(lli array[], int n, int logn)
{
  for (int i = 0; i < n; i ++) sparseTable[i][0] = array[i];
  for (int j = 1; j <= logn; j ++)
    for (int i = 0, shift = (1 << (j - 1)); i + shift < n; i ++)
      sparseTable[i][j] = f(sparseTable[i][j - 1], sparseTable[i + shift][j - 1]);
}

lli query(int lo, int hi)
{
  int qs = logdp[hi - lo + 1];
  return(f(sparseTable[lo][qs], sparseTable[hi - (1 << qs) + 1][qs]));
  lli ans = zero;
  for (int j = maxLog; j >= 0; j --)
    if (lo + (1 << j) - 1 <= hi)
    {
      ans = f(ans, sparseTable[lo][j]);
      lo += (1 << j);
    }
  return(ans);
}

// 0 1 2 3 4 5 6 7 8 9 (size of the query)
// - 0 1 1 2 2 2 2 3
void fillLogDP()
{
  logdp[1] = 0;
  for (int i = 2; i <= maxSize; i ++) logdp[i] = logdp[i >> 1] + 1;
}

int main()
{
  int n; scanf("%d", &n);
  lli array[n]; for (int i = 0; i < n; i ++) scanf("%lld", &array[i]);
  int logn = floor(log2(n)) + 1;
  // printf("size: %d, logn: %d\n", n, logn);

  build(array, n, logn); fillLogDP();
  // for (int i = 0; i < n; i ++) printArray(sparseTable[i], logn + 1);

  int lo, hi;
  while (scanf("%d %d", &lo, &hi) != EOF)
    printf("[%d, %d] = %lld\n", lo, hi, query(lo, hi));

  return(0);
}
/*
void build(lli array[], int n, int logn)
{
  for (int i = 0; i < n; i ++) sparseTable[i][0] = f(array[i], array[i]);
  for (int j = 1; j <= logn; j ++)
    for (int i = 0; i + (1 << (j - 1)) < n; i ++)
      sparseTable[i][j] = f(sparseTable[i][j - 1], sparseTable[i + (1 << (j - 1))][j - 1]);
}

lli query(int lo, int hi)
{
  lli fim = zero;
  for (int j = maxLog; j >= 0; j --)
    if (lo + (1 << j) - 1 <= hi)
    {
      fim = f(fim, sparseTable[lo][j]);
      lo += (1 << j);
    }
  return(fim);
}
*/