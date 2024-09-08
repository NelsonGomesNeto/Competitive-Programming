#include <stdio.h>
#define lli long long int

int n;
lli a[400000];

int main()
{
  while (scanf("%d", &n) != EOF)
  {
    for (int i = 0; i < n; i ++)
      scanf("%lld", &a[i]);
    lli ans = 0;
    for (int i = 0; i < n - 1; i ++)
      ans ^= a[i] ^ a[i + 1];
    printf("%lld\n", ans);
  }
  return 0;
}
