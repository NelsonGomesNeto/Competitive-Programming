#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

int main()
{
  int n, m; scanf("%d %d", &n, &m);
  int ans = 1e9;
  for (int i = 1; i * m <= n; i ++)
    if (2 * i * m >= n)
      ans = min(ans, i*m);
  if (ans == 1e9)
    ans = -1;
  printf("%d\n", ans);

  return 0;
}