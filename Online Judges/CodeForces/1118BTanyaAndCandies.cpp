#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 2e5; int n;
int a[maxN];
lli even[maxN + 1], odd[maxN + 1];

int main()
{
  scanf("%d", &n);
  for (int i = 0; i < n; i ++)
  {
    scanf("%d", &a[i]);
    even[i + 1] = even[i], odd[i + 1] = odd[i];
    if (i & 1) odd[i + 1] += a[i];
    else even[i + 1] += a[i];
  }

  int ans = 0;
  for (int i = 0; i < n; i ++)
  {
    lli oddSum = even[i] + odd[n] - odd[i + 1];
    lli evenSum = odd[i] + even[n] - even[i + 1];
    // printf("%lld %lld\n", evenSum, oddSum);
    if (evenSum == oddSum)
      ans ++;
  }
  printf("%d\n", ans);

  return 0;
}