#include <bits/stdc++.h>
#define DEBUG if(1)
using namespace std;


int main()
{
  int a, b, x; scanf("%d %d %d", &a, &b, &x);
  int n = a + b, big = max(a, b), small = min(a, b);

  int ans[n]; memset(ans, 0, sizeof(ans));
  big --;
  for (int i = 1; i < n;)
  {
    while (i < n && x > 1 && small && big)
    {
      ans[i] = 1;
      if (i == n - 1) x ++;
      i += 2;
      x -= 2;
      big --;
      small --;
    }
    if (!x)
    {
      i --; big ++;
      while (i < n && small)
      {
        ans[i] = 1;
        i ++;
        small --;
      }
      while (i < n && big)
      {
        i ++;
        big --;
      }
    }
    else
    {
      while (i < n && big)
      {
        i ++;
        big --;
      }
      while (i < n && small)
      {
        ans[i] = 1;
        i ++;
        small --;
      }
    }
  }

  for (int i = 0; i < n; i ++) printf("%d", ans[i] ? a > b : a <= b); printf("\n");

  return(0);
}