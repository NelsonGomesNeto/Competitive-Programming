#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxK = 4e5; lli n; int k;
lli x[maxK];

int main()
{
  int t; scanf("%d", &t);
  for (int tt = 1; tt <= t; tt++)
  {
    scanf("%lld %d", &n, &k);
    for (int i = 0; i < k; i++)
      scanf("%lld", &x[i]);

    sort(x, x+k);

    lli currTime = 0; int ans = 0;
    for (int i = k - 1; i >= 0; i--)
    {
      if (currTime >= x[i]) break;
      currTime += n - x[i];
      ans++;
    }
    printf("%d\n", ans);
  }
  return 0;
}
