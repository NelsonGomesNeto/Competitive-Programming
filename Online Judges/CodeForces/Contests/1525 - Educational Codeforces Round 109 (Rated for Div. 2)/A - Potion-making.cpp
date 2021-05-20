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
    int k; scanf("%d", &k);
    int ans = 1;
    int w = 1, e = 0;
    while (true)
    {
      if (e * 100 / (e + w) < (100 - k))
        e++;
      else if (w * 100 / (e + w) < k)
        w++;
      else
        break;
      ans++;
    }
    printf("%d\n", ans);
  }
  return 0;
}
