#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 3e5; int n;
lli a[maxN], b[maxN];

lli aux[maxN];
lli merge(int lo, int mid, int hi)
{
  lli inv = 0; int total = hi - lo + 1;
  for (int i = lo, j = mid + 1, k = 0; k < total; k++)
    if (i <= mid && (j > hi || b[i] <= b[j]))
      aux[k] = b[i++];
    else
      aux[k] = b[j++], inv += mid - i + 1;
  for (int k = 0; k < total; k++)
    b[lo + k] = aux[k];
  return inv;
}
lli inversions(int lo = 0, int hi = n - 1)
{
  if (lo == hi) return 0;
  int mid = (lo + hi) >> 1;
  lli inv = inversions(lo, mid) + inversions(mid + 1, hi);
  inv += merge(lo, mid, hi);
  return inv;
}

int main()
{
  while (scanf("%d", &n) != EOF)
  {
    for (int i = 0; i < n; i++)
      scanf("%lld", &a[i]);

    for (int i = 0; i < n; i++)
      b[i] = a[i];
    lli normal = inversions();

    lli x = 0;
    lli curr = 0;
    for (int p = 29; p >= 0; p--)
    {
      lli bitmask = (1LL << p);

      for (int i = 0; i < n; i++)
        b[i] = a[i] ^ bitmask;
      lli diff = inversions();

      if (diff < normal)
        x |= bitmask;
    }

    for (int i = 0; i < n; i++)
      b[i] = a[i] ^ x;
    lli total = inversions();
    printf("%lld %lld\n", total, x);
  }
  return 0;
}
