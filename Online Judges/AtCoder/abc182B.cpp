#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 1e2, maxX = 1e4; int n;
int a[maxN];

int main()
{
  while (scanf("%d", &n) != EOF)
  {
    for (int i = 0; i < n; i++)
      scanf("%d", &a[i]);

    int cnt = -1, ans = -1;
    for (int d = 2; d <= maxX; d++)
    {
      int c = 0;
      for (int i = 0; i < n; i++)
        c += a[i] % d == 0;
      if (c > cnt)
        cnt = c, ans = d;
    }
    printf("%d\n", ans);
  }
  return 0;
}