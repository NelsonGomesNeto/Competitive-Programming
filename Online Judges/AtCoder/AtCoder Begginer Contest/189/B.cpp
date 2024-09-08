#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

int main()
{
  int n, x;
  while (~scanf("%d %d", &n, &x))
  {
    x *= 100;
    int ans = -1;
    for (int i = 0; i < n; i++)
    {
      int v, p; scanf("%d %d", &v, &p);
      x -= v * p;
      if (x < 0 && ans == -1)
        ans = i + 1;
    }
    printf("%d\n", ans);
  }
  return 0;
}