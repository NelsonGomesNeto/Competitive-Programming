#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 1e5; int n, q;
int a[maxN];

int main()
{
  // int t; scanf("%d", &t);
  // for (int tt = 1; tt <= t; tt++)
  {
    scanf("%d %d", &n, &q);
    for (int i = 0; i < n; i++)
      scanf("%d", &a[i]);;
    int ones = 0;
    for (int i = 0; i < n; i++)
      ones += a[i];

    for (int i = 0; i < q; i++)
    {
      int op, x; scanf("%d %d", &op, &x);
      if (op == 1)
      {
        ones -= a[x - 1];
        a[x - 1] = 1 - a[x - 1];
        ones += a[x - 1];
      }
      else
        printf("%d\n", x <= ones);
    }
  }
  return 0;
}
