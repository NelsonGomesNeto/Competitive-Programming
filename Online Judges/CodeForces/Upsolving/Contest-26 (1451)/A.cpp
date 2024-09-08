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
    int n; scanf("%d", &n);
    int ans;
    if (n == 1)
      ans = 0;
    else if (n == 2)
      ans = 1;
    else if (n == 3)
      ans = 2;
    else
      ans = n & 1 ? 3 : 2;
    printf("%d\n", ans);
  }
  return 0;
}
