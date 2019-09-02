#include <bits/stdc++.h>
#define lli long long int
using namespace std;

int main()
{
  int t;
  scanf("%d", &t);
  while (t --)
  {
    int b, p, f; scanf("%d %d %d", &b, &p, &f);
    int h, c; scanf("%d %d", &h, &c);
    int ans = 0;
    for (int j = 1; j <= (b >> 1); j ++)
    {
      int aa = min(j, p);
      ans = max(ans, aa*h + min((b >> 1) - aa, f)*c);
    }
    for (int j = 1; j <= (b >> 1); j ++)
    {
      int aa = min(j, f);
      ans = max(ans, aa*c + min((b >> 1) - aa, p)*h);
    }
    printf("%d\n", ans);
  }
  return(0);
}
