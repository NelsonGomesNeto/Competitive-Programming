#include <bits/stdc++.h>
#define DEBUG if(0)
using namespace std;

int main()
{
  int n, x; scanf("%d %d", &n, &x);
  int a[n]; for (int i = 0; i < n; i ++) scanf("%d", &a[i]);
  sort(a, a+n);

  int ans = 0;
  if (a[(n + 1) / 2 - 1] == x) printf("0\n");
  else
  {
    if (a[n - 1] < x) printf("%d\n", n + 1);
    else if (a[0] > x) printf("%d\n", n);
    else
    {
      int pos;
      if (x < a[(n + 1) / 2 - 1]) pos = (upper_bound(a, a+n, x) - a) - 1;
      else pos = lower_bound(a, a+n, x) - a;
      DEBUG printf("pos: %d %d %d\n", pos, (n + 1)/2 - 1, a[(n + 1) / 2 - 1]);
      if (pos > (n+1) / 2 - 1) printf("%d\n", 2 * pos - n + 1);
      else printf("%d\n", n-2*(pos+1));
    }
  }
  // (n + x + 1) / 2 - 1 = pos
  // n + x + 1 = 2 * pos + 2
  // x = 2 * pos - n + 1

  return(0);
}