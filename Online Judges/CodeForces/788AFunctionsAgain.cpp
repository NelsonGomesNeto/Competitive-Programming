#include <bits/stdc++.h>
using namespace std;
#define DEBUG if(0)
#define lli long long int

void printArray(lli a[], int size)
{
  for (int i = 0; i < size; i ++) printf("%lld ", a[i]);
  printf("\n");
}

lli f(int l, int r, lli a[])
{
  lli s = 0, k = 1;
  for (int i = l; i <= r - 1; i ++, k *= -1)
    s += abs(a[i] - a[i + 1]) * k;
  return(s);
}

int main()
{
  int n; scanf("%d", &n);
  lli a[n]; for (int i = 0; i < n; i ++) scanf("%lld", &a[i]);

  lli sum[n]; sum[0] = f(0, 1, a);
  for (int i = 1; i < n - 1; i ++)
    sum[i] = f(i, i + 1, a);
  DEBUG printArray(sum, n);

  lli maximum = -999999999999, now = 0, now2 = 0, k = 1;
  for (int i = 0; i < n - 1; i ++, k *= -1)
  {
    now += sum[i] * k; now2 += sum[i] * (-k);
    maximum = max(maximum, max(now, now2));
    if (now < 0) now = 0;
    if (now2 < 0) now2 = 0;
  }

  printf("%lld\n", maximum);

  return(0);
}
