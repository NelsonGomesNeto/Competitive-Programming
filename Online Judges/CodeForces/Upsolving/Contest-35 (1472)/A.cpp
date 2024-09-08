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
    int w, h, n; scanf("%d %d %d", &w, &h, &n);
    int wt = 1, ht = 1;
    while (!(w & 1))
    {
      wt *= 2;
      w >>= 1;
    }
    while (!(h & 1))
    {
      ht *= 2;
      h >>= 1;
    }
    DEBUG printf("\t%d %d\n", wt, ht);
    printf("%s\n", wt * ht >= n ? "YES" : "NO");
  }
  return 0;
}
