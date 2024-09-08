#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

int main()
{
  int t; scanf("%d", &t);
  for (int tt = 1; tt <= t; tt++)
  {
    int x, y; scanf("%d %d", &x, &y);
    int ans = 2*min(x, y);

    int left = max(x, y) - min(x, y);
    DEBUG printf("\t%d %d\n", ans, left);
    while (left > 1)
    {
      ans += 1 + 1;
      left -= 1;
    }
    ans += left;

    printf("%d\n", ans);
  }
  return 0;
}
