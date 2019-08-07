#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
using namespace std;

void printArray(lli a[], int size)
{
  for (int i = 0; i < size; i ++) printf("%lld%c", a[i], i < size - 1 ? ' ' : '\n');
}

int main()
{
  int n, m; scanf("%d %d", &n, &m);
  int a[n + 2]; a[0] = 0;
  for (int i = 1; i <= n; i ++) scanf("%d", &a[i]);
  a[n + 1] = m;

  lli even[n + 2], odd[n + 2]; even[0] = 0; odd[0] = 0;
  for (int i = 0, k = 1; i <= n; i ++, k = !k)
  {
    even[i + 1] = even[i] + (a[i + 1] - a[i]) * k;
    odd[i + 1] = odd[i] + (a[i + 1] - a[i]) * (!k);
  }
  DEBUG printArray(even, n + 2);
  DEBUG printArray(odd, n + 2);

  lli best = even[n + 1];
  if (a[1] > 1) best = max(best, 1 + odd[n + 1] - (even[1] - 1));
  for (int i = 1; i <= n; i ++)
  {
    best = max(best, (even[i] - even[0] - 1) + (odd[n + 1] - odd[i]));
  }

  printf("%lld\n", best);

  return(0);
}