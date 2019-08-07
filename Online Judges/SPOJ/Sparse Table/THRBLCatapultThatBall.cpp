#include <bits/stdc++.h>
using namespace std;
#define lli long long int
const int maxSize = 1e6, maxLog = floor(log2(1e6)) + 1;
lli sparseTable[maxSize][maxLog + 1], logdp[maxSize + 1];
lli zero = LLONG_MIN;

void swap(int *a, int *b)
{
  int aux = *a;
  *a = *b;
  *b = aux;
}

void fillLogDP()
{
  logdp[1] = 0;
  for (int i = 2; i <= maxSize; i ++) logdp[i] = logdp[i >> 1] + 1;
}

void build(lli a[], int n, int logn)
{
  for (int i = 0; i < n; i ++) sparseTable[i][0] = a[i];
  for (int j = 1; j <= logn; j ++)
    for (int i = 0, shift = (1 << (j - 1)); i + shift < n; i ++)
      sparseTable[i][j] = max(sparseTable[i][j - 1], sparseTable[i + shift][j - 1]);
}

lli query(int lo, int hi)
{
  int qs = logdp[hi - lo + 1];
  return(max(sparseTable[lo][qs], sparseTable[hi - (1 << qs) + 1][qs]));
  lli ans = zero;
  for (int j = maxLog; j >= 0; j --)
    if (lo + (1 << j) - 1 <= hi)
    {
      ans = max(ans, sparseTable[lo][j]);
      lo += (1 << j);
    }
  return(ans);
}

int main()
{
  int n, m; scanf("%d %d", &n, &m);
  lli h[n]; for (int i = 0; i < n; i ++) scanf("%lld", &h[i]);
  build(h, n, floor(log2(n)) + 1); fillLogDP();

  int ans = 0, lo, hi;
  while (m --)
  {
    scanf("%d %d", &lo, &hi); lo --, hi --;
    if (lo > hi) swap(&lo, &hi);
    ans += h[lo] >= query(lo, hi - 1);
  }
  printf("%d\n", ans);
  return(0);
}