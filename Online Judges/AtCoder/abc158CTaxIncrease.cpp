#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

int a, b;

int main()
{
  while (scanf("%d %d", &a, &b) != EOF)
  {
    int ans;
    for (ans; ans < 1e7; ans ++)
    {
      DEBUG printf("%d - %d %d\n", ans, (int)(ans * 8 / 100.0), (int)(ans / 10.0));
      if ((int)(ans * 8 / 100.0) == a && (int)(ans / 10.0) == b)
        break;
    }
    if (ans == 1e7) ans = -1;
    printf("%d\n", ans);
  }
  return 0;
}