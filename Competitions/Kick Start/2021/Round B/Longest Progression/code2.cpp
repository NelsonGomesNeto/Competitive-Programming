#include <bits/stdc++.h>
#define DEBUG if(0)
#define lli long long int
#define ldouble long double
using namespace std;

const int maxN = 3e5; int n;
lli a[maxN];
map<lli, int> deltaCnt;

int main()
{
  int t; scanf("%d", &t);
  for (int tt = 1; tt <= t; tt++)
  {
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
      scanf("%lld", &a[i]);

    deltaCnt.clear();
    int ans = 0;
    for (int i = 1; i < n; i++)
    {
      lli delta = (a[i] - a[i - 1]);
      bool used = false;

      int j = i;
      while (j + 1 < n && ((a[j + 1] - a[j]) == delta || !used))
      {
        if ((a[j + 1] - a[j]) != delta)
          used = true, j += 2;
        else
          j++;
      }
      if (j == n) j--;

      DEBUG printf("%d - %lld - %d - %d\n", i, delta, used, j);

      ans = max(ans, j - i + 2 + (!used && !(i == 1 && j == n - 1)));

      i = j;
    }

    printf("Case #%d: %d\n", tt, ans);
  }
  return 0;
}