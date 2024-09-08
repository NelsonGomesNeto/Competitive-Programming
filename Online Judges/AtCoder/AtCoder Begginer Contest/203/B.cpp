#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

int main()
{
  int n, k;
  while (~scanf("%d %d", &n, &k))
  {
    int ans = 0;
    for (int i = 1; i <= n; i++)
      for (int j = 1; j <= k; j++)
        ans += 100 * i + j;
    printf("%d\n", ans);
  }
  return 0;
}