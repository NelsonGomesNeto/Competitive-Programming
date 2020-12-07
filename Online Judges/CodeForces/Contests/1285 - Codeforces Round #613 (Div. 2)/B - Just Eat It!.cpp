#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 1e5; int n;
lli a[maxN];

int main()
{
  int t; scanf("%d", &t);
  while (t --)
  {
    scanf("%d", &n);
    lli s = 0;
    bool won = true;
    for (int i = 0; i < n; i ++)
    {
      scanf("%lld", &a[i]);
      s += a[i];
    }
    lli now = 0;
    for (int i = 0; i < n - 1; i ++)
    {
      now += a[i];
      if (now >= s)
        won = false;
      if (now < 0)
        now = 0;
    }
    now = 0;
    for (int i = 1; i < n; i ++)
    {
      now += a[i];
      if (now >= s)
        won = false;
      if (now < 0)
        now = 0;
    }

    printf("%s\n", won ? "YES" : "NO");
  }
  return 0;
}
