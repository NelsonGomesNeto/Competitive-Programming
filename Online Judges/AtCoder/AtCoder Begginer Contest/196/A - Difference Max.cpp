#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

int main()
{
  int a, b, c, d;
  while (~scanf("%d %d %d %d", &a, &b, &c, &d))
  {
    int ans = -1e9;
    for (int x = a; x <= b; x++)
      for (int y = c; y <= d; y++)
        ans = max(ans, x - y);
    printf("%d\n", ans);
  }
  return 0;
}