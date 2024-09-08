#include <bits/stdc++.h>
#define lli long long int

int main()
{
  lli size; scanf("%lld", &size);
  lli a[size], mean = 0;
  for (int i = 0; i < size; i ++)
  {
    scanf("%lld", &a[i]);
    mean += a[i];
  }
  mean = ceil((double) mean / 2);
  int index = -1; lli sum = 0;
  for (int i = 0; i < size; i ++)
  {
    sum += a[i];
    if (sum >= mean && index == -1) index = i;
  }
  printf("%d\n", index + 1);
  return(0);
}
