#include <bits/stdc++.h>
#define lli long long int
using namespace std;

const int maxK = 8, maxN = 1e5; int W, D, A, K;
const long double eps = 1e-10;
long double p[2][maxK + 1], q[2][maxK + 1];
long double f[2][maxN], dx, dx2;
void read(long double arr[])
{
  for (int i = 0; i <= K; i ++)
    scanf("%Lf", &arr[i]);
}

long double calc(long double x, int eq)
{
  long double pSum = 0, qSum = 0, xx = 1;
  for (int i = 0; i <= K; i ++, xx *= x)
    pSum += p[eq][i] * xx, qSum += q[eq][i] * xx;
  return(pSum / qSum);
}
long double evaluate(long double d)
{
  long double a = 0;
  for (int i = 0; i < maxN; i ++)
  {
    long double y1 = f[0][i], below = max(f[1][i], d);
    if (below < y1) a += (y1 - below) * dx;
  }
  return(a);
}

long double binarySearch(long double target = A, long double lo = 0, long double hi = D)
{
  while (hi - lo >= eps)
  {
    long double mid = (lo + hi) / 2.0;
    if (evaluate(-mid) > target) hi = mid;
    else lo = mid;
  }
  return(lo);
}

int main()
{
  while (scanf("%d %d %d %d", &W, &D, &A, &K) != EOF)
  {
    read(p[0]); read(q[0]);
    read(p[1]); read(q[1]);

    int i = 0; dx = (long double) W / maxN; dx2 = dx / 2.0;
    for (long double x = 0; i < maxN; i ++, x += dx)
      f[0][i] = calc(x + dx2, 0), f[1][i] = calc(x + dx2, 1);

    long double ans = binarySearch();
    printf("%.5Lf\n", ans);
    // printf("%.5Lf -- %.5Lf\n", ans, evaluate(-ans));
  }
  return(0);
}