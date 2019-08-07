#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int

void printArray(lli a[], int size)
{
  for (int i = 0; i < size; i ++)
    printf("%lld ", a[i]);
  printf("\n");
}

int main()
{
  int n; scanf("%d", &n);
  lli a[n], s = 0;
  for (int i = 0; i < n; i ++)
  {
    scanf("%lld", &a[i]);
    s += a[i];
  }
  DEBUG printArray(a, n);

  if (s % 3)
    printf("0\n");
  else
  {
    lli ways = 0; lli sum = s / 3;
    DEBUG printf("Target sum: %lld\n", sum);

    lli ap[n]; memset(ap, 0, sizeof(ap));
    s = a[0]; ap[0] = a[0] == sum;
    for (int i = 1; i < n - 2; i ++)
    {
      s += a[i];
      ap[i] = (s == sum);
    }
    DEBUG printArray(ap, n);

    lli cp[n]; memset(cp, 0, sizeof(cp));
    s = a[n - 1]; cp[n - 1] = a[n - 1] == sum;
    for (int i = n - 2; i > 1; i --)
    {
      s += a[i];
      cp[i] = cp[i + 1] + (s == sum);
    }
    DEBUG printArray(cp, n);

    lli total = 0;
    for (int i = 0; i < n - 2; i ++)
      if (ap[i]) total += cp[i + 2];
    printf("%lld\n", total);
  }

  return(0);
}
