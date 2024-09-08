#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

int x, y;

int main()
{
  int t; scanf("%d", &t);
  for (int tt = 1; tt <= t; tt++)
  {
    scanf("%d %d", &x, &y);
    int ans = min(20 * (x - 1), 5 * (y - 1) + 5 * (x - 1));
    printf("%d\n", ans);
  }
  return 0;
}