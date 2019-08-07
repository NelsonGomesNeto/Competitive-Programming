#include <bits/stdc++.h>
#define lli long long int

int main()
{
  int n; scanf("%d", &n);
  lli sum = 0, num;
  for (int i = 0; i < n; i ++)
  {
    scanf("%lld", &num);
    sum += num;
  }

  printf("%lld\n", sum);

  return(0);
}