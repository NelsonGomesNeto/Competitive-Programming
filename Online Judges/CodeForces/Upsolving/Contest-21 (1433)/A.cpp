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
    int x; scanf("%d", &x);
    int ans = 0; bool done = false;
    for (int i = 1; i <= 9 && !done; i++)
      for (int j = 1; j <= 4 && !done; j++)
      {
        ans += j;
        int now = 0;
        for (int k = 1, kk = 0; kk < j; k *= 10, kk++)
          now += i * k;
        if (now == x)
          done = true;
      }

    printf("%d\n", ans);
  }
  return 0;
}
